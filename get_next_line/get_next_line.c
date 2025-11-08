/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-bo <abdel-bo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 01:42:53 by abdel-bo          #+#    #+#             */
/*   Updated: 2025/04/27 20:58:52 by abdel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_verify(char *tmp, char *buff)
{
	char	*new_tmp;

	if (!buff)
		return (tmp);
	if (!tmp)
		return (ft_strdup(buff));
	new_tmp = (char *)malloc(ft_strlen(tmp) + ft_strlen(buff) + 1);
	if (!new_tmp)
	{
		free(tmp);
		return (NULL);
	}
	ft_memcpy(new_tmp, tmp, ft_strlen(tmp));
	ft_memcpy(new_tmp + ft_strlen(tmp), buff, ft_strlen(buff));
	new_tmp[ft_strlen(tmp) + ft_strlen(buff)] = '\0';
	free(tmp);
	return (new_tmp);
}

static void	ft_extract(char **ptr)
{
	char	*keep_tmp;
	char	*newline;

	if (!ptr || !*ptr)
		return ;
	newline = ft_strchr(*ptr, '\n');
	if (!newline)
		return ;
	*newline = '\0';
	keep_tmp = ft_strdup(newline + 1);
	free(*ptr);
	*ptr = keep_tmp;
}

static void	ft_free_ptr(char **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

static char	*ft_free(char **ptr_tmp, char **ptr_buff, ssize_t b)
{
	char	*line;

	line = NULL;
	if (ptr_buff && *ptr_buff)
	{
		free(*ptr_buff);
		*ptr_buff = NULL;
	}
	if (!ptr_tmp || !*ptr_tmp)
		return (NULL);
	if (**ptr_tmp && b == 0)
	{
		line = ft_strdup(*ptr_tmp);
		free(*ptr_tmp);
		*ptr_tmp = NULL;
		return (line);
	}
	if (ft_strchr(*ptr_tmp, '\n'))
	{
		line = ft_substr(*ptr_tmp, 0, ft_strchr(*ptr_tmp, '\n') - *ptr_tmp + 1);
		ft_extract(ptr_tmp);
		return (line);
	}
	ft_free_ptr(ptr_tmp);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*tmp;
	char		*buff;
	ssize_t		read_byte;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = (char *)malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	read_byte = 1;
	while (read_byte > 0)
	{
		if (tmp && ft_strchr(tmp, '\n'))
			return (free(buff), ft_free(&tmp, NULL, read_byte));
		read_byte = read(fd, buff, BUFFER_SIZE);
		if (read_byte <= 0)
			break ;
		buff[read_byte] = '\0';
		tmp = ft_verify(tmp, buff);
		if (!tmp)
			break ;
	}
	free(buff);
	return (ft_free(&tmp, NULL, read_byte));
}
/*
int main(int argc, char **argv)
{
	int	fd;
	char	*line;

	if (argc != 2)
	{
		printf("Usage: %s <filename>\n", argv[0]);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}*/
