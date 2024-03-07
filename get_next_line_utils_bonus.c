/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:24:39 by ewoillar          #+#    #+#             */
/*   Updated: 2024/03/07 13:12:01 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

char	*get_line(char **remainder)
{
	char	*line;
	char	*temp;
	int		i;

	i = 0;
	while ((*remainder)[i] != '\n' && (*remainder)[i] != '\0')
		i++;
	if ((*remainder)[i] == '\n' && (*remainder)[i + 1] != '\0')
	{
		line = ft_substr(*remainder, 0, i + 1);
		if (!line)
			return (NULL);
		temp = ft_strdup(*remainder + i + 1);
		if (!temp)
		{
			free(line);
			return (NULL);
		}
		free(*remainder);
		*remainder = temp;
	}
	else
		line = get_line_null(remainder, &line);
	return (line);
}

int	has_newline(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*result;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (len == 1)
		return (NULL);
	result = malloc(len * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s1))
	{
		result[i] = s1[i];
		i++;
	}
	j = -1;
	while (++j < ft_strlen(s2))
		result[i + j] = s2[j];
	result[i + j] = '\0';
	free(s1);
	return (result);
}

char	*ft_strdup(const char *s)
{
	char	*str;
	int		len;
	int		i;

	len = 0;
	if (!s)
		return (NULL);
	while (s[len])
		len++;
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	if (!s)
		return (NULL);
	substr = malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len && s[start + i] != '\0')
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
