/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:01:59 by ewoillar          #+#    #+#             */
/*   Updated: 2024/03/07 13:41:03 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

char	*get_line_null(char **remainder, char **line)
{
	*line = ft_strdup(*remainder);
	if (!(*line))
		return (NULL);
	free(*remainder);
	*remainder = NULL;
	return (*line);
}

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
		len++;
	return (len);
}

char	*get_next_line(int fd)
{
	static char	**remainder;
	char		*buffer;
	int			bytes_read;
	char		*line;

	if(!remainder)
	{
		remainder = malloc(sizeof(char *) * 1025);
		if (!remainder)
			return (NULL);
	}
	if (fd <= 0)
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	if (!remainder[fd])
		remainder[fd] = NULL;
	while (!has_newline(remainder[fd]) && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		remainder[fd] = ft_strjoin(remainder[fd], buffer);
	}
	free(buffer);
	if (bytes_read == 0 && !remainder[fd])
		return (NULL);
	line = get_line(&remainder[fd]);
	return (line);
}
/*
int	main(void)
{
	int	fd = open("b.txt", O_RDONLY);
	char	*buffer;

	buffer = get_next_line(fd);
	printf("%s", buffer); free(buffer);
	buffer = get_next_line(fd);
        printf("%s", buffer); free(buffer);
	buffer = get_next_line(fd);
        printf("%s", buffer); free(buffer);
	buffer = get_next_line(fd);
        printf("%s", buffer); free(buffer);
	buffer = get_next_line(fd);
        printf("%s", buffer); free(buffer);
	buffer = get_next_line(fd);
        printf("%s", buffer); free(buffer);
	close(fd);
}*/
