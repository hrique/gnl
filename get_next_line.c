/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hesantan <hesantan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 13:59:35 by hesantan          #+#    #+#             */
/*   Updated: 2026/07/02 18:54:06 by hesantan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*get_next_line(int fd)
{
	static char	*storage; // guarda o resultado do que foi lido
	char		*line; //guarda uma linha
	storage = read_line(storage, fd); // manda o arquivo recebido para ser lido
	line = get_line(storage); //retorno do get_line
	storage = update_storage(storage);
	return(line); //retorna a linha para o usuario (encerra a funçao)
}

//ssize_t read(int fd, void *buf, size_t count)

static read_line(char *storage, int fd) //passa o que ela fez para o get_line antes do '\n'
{
	long	bytes_lidos;
	char	*reading;

	while ("nao chegou no \n")
	{
		bytes_lidos = read(fd, reading, BUFFER_SIZE); //conta quantos bytes lidos
		storage = ft_strjoin(storage, reading); //concatena o storage com o que foi lido
	}
	return (storage);
}

static get_line(char *storage) //Extrair o que o read leu
{
	int		i;
	char	*str;

	i = 0;
	while (storage[i] != '\n' && storage[i])
	{
		i++;
	}
	str = ft_substr(storage, 0, i); //pegar tudo antes do \n
	return (str);
}

static update_storage(char *storage) //se tem alguma coisa depois do \n ele guarda essa coisa
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (storage[i])
		i++;
	j = 0;
	while (storage[j] != '\n')
		j++;
	if (storage[j] == '\0')
		return (NULL);
	str = ft_substr(storage, j, (i - j));
	return (str);
}
