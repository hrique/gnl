*This project has been created as part of the 42 curriculum by hesantan*

# get_next_line

A 42 School project that implements a function able to read, line by line, the content of any file descriptor — a file, `stdin`, or a pipe — without relying on the libc's built-in line-reading functions.

## Table of contents

- [How it works](#how-it-works)
- [Files](#files)
- [Compilation](#compilation)
- [Usage](#usage)
- [BUFFER_SIZE](#buffer_size)
- [Bonus: multiple file descriptors](#bonus-multiple-file-descriptors)
- [Memory management](#memory-management)
- [Known limitations](#known-limitations)
- [Norminette](#norminette)

## How it works

`get_next_line` reads the `fd` in chunks of `BUFFER_SIZE` bytes, using `read()`, and accumulates that content into a static buffer (`storage`) until it finds a `\n` or the file ends. On each call:

1. If `storage` doesn't already contain a complete line, more data is read from `fd` and appended to what's already there.
2. The complete line (up to and including the `\n`, if present) is extracted from `storage`.
3. That line is removed from `storage`, keeping the remainder for the next call.
4. The extracted line is returned, or `NULL` when there's nothing left to read.

Persistence between calls is handled with a `static` variable, which keeps the unread remainder of the file from one call to the next without needing to reopen or re-scan the `fd`.

## Files

| File | Responsibility |
|---|---|
| `get_next_line.c` | Main logic (mandatory) |
| `get_next_line.h` | Prototypes and `BUFFER_SIZE` (mandatory) |
| `get_next_line_utils.c` | Helper functions (`ft_strjoin`, `ft_substr`, `ft_calloc`, `ft_strchr`, `ft_memcpy`) |
| `get_next_line_bonus.c` | Main logic with multi-fd support (bonus) |
| `get_next_line_bonus.h` | Prototypes, `BUFFER_SIZE`, and `FD_MAX` (bonus) |
| `get_next_line_utils_bonus.c` | Same helper functions, used by the bonus version |

### Internal functions

- **`read_line`** — reads from `fd` in `BUFFER_SIZE` chunks until it finds `\n` or the file ends.
- **`get_line`** — extracts the first complete line from `storage`.
- **`update_storage`** — removes the already-extracted line, keeping only the remainder in `storage`.
- **`free_and_null`** — frees auxiliary buffers on error paths and returns `NULL`, avoiding repeated `free` calls scattered throughout the code.

## Compilation

The project has no `main`, so it's meant to be compiled alongside a test program:

```bash
# mandatory
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl

# bonus
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c -o gnl_bonus
```

`BUFFER_SIZE` can be omitted — in that case it falls back to the default value defined in the header (`5`).

## Usage

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int		fd;
	char	*line;

	fd = open("file.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Error while opening the file\n");
		return (1);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	printf("\n");
	close(fd);
	return (0);
}
```

Each returned line includes the trailing `\n`, except for the last line of the file if it doesn't end with a newline.

## BUFFER_SIZE

Defines how many bytes are read from `fd` per `read()` call. Set via `-D BUFFER_SIZE=n` at compile time, falling back to `5` if not specified. Tested and validated for values ranging from `1` to `10000000`.

Very small values (such as `1`) increase the number of `read()` calls and internal reallocations — see [Known limitations](#known-limitations).

## Bonus: multiple file descriptors

The bonus version (`get_next_line_bonus.c`) supports reading from several `fd`s simultaneously and in interleaved order, without mixing content between them:

```c
int fd1 = open("a.txt", O_RDONLY);
int fd2 = open("b.txt", O_RDONLY);

char *l1 = get_next_line(fd1);
char *l2 = get_next_line(fd2);
char *l1_next = get_next_line(fd1); // continues from where fd1 left off, unaffected by fd2
```

This works because the static variable is no longer a single pointer but an array indexed by the `fd` itself:

```c
static char *storage[FD_MAX];
```

`FD_MAX` (defined in `get_next_line_bonus.h`, default value `1024`) bounds the array size and is validated before any access (`fd >= FD_MAX` returns `NULL`), preventing out-of-bounds array access.

## Memory management

Validated with Valgrind, with no leaks and no invalid read/write, covering:

- Normal reads through EOF, with and without a trailing `\n`.
- Invalid `fd` (`read()` returning `-1`).
- Empty file.
- Simulated allocation failure (`ft_calloc` returning `NULL`).
- Multiple lines, including empty lines and interleaved reads across multiple fds (bonus).

Points that required special attention during development:

- The `static` variable must be explicitly reset to `NULL` (`storage = NULL`) after being freed — just calling `free()` on its value doesn't change the content of the static variable itself, and reusing it afterward causes a use-after-free.
- Every error path inside `read_line` needs to free both the temporary read buffer (`reading`) and the `storage` accumulated up to that point, not just one of the two.

## Known limitations

With `BUFFER_SIZE = 1` and a very large line (tens of thousands of characters or more), reading becomes slow. This happens because on every single byte read, the entire `storage` is rebuilt from scratch via `ft_strjoin` (allocating a new buffer and copying everything again), which results in O(n²) complexity to assemble one large line. This is not a correctness bug — the final result is always correct — it's a performance limitation of the incremental concatenation strategy used here, common to GNL implementations built on `ft_strjoin`.

## Norminette

Both versions (mandatory and bonus) comply with:
- A maximum of 5 functions per `.c` file.
- A maximum of 25 lines per function.
- No global variables.