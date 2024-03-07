/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:01:59 by ewoillar          #+#    #+#             */
/*   Updated: 2024/03/07 13:03:03 by ewoillar         ###   ########.fr       */
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
	static char	*remainder;
	char		*buffer;
	int			bytes_read;
	char		*line;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!has_newline(remainder) && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		remainder = ft_strjoin(remainder, buffer);
	}
	free(buffer);
	if (bytes_read == 0 && !remainder)
		return (NULL);
	line = get_line(&remainder);
	return (line);
}

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
}
