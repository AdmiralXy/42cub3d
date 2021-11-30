/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faggar <faggar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 19:37:29 by faggar            #+#    #+#             */
/*   Updated: 2021/09/15 17:38:55 by faggar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../fdf.h"

char	*setter(char *prevBuf, char **line)
{
	char	*point;

	point = NULL;
	if (prevBuf)
	{
		point = ft_strchr(prevBuf, '\n');
		if (point)
		{
			*point = '\0';
			*line = ft_strdup(prevBuf);
			ft_strcpy(prevBuf, ++point);
		}
		else
		{
			*line = ft_strdup(prevBuf);
		}
	}
	else
	{
		*line = malloc(1);
		*line[0] = 0;
	}
	return (point);
}

int	to_return(char *line, char **prevBuf, int eof, char *buf)
{
	free(buf);
	if (eof <= 0)
	{
		if (*prevBuf)
		{
			free (*prevBuf);
			*prevBuf = NULL;
		}
		if (eof == 0)
			return (0);
		else
			return (-1);
	}
	if (eof != 0 || (*prevBuf) || (line))
		return (1);
	return (0);
}

char	*change(char **point, char **prevBuf)
{
	char	*str;

	str = *point;
	*str = 0;
	str++;
	if (*prevBuf)
	{
		free(*prevBuf);
		prevBuf = NULL;
	}
	return (ft_strdup(str));
}

int	get_next_line(int fd, char **line)
{
	t_gnl		params;
	static char	*prevBuf;

	if (fd < 0 || line == NULL)
		return (-1);
	params.buf = malloc(sizeof(char) * (10 + 1));
	if (!params.buf)
		return (-1);
	params.eof = 1;
	params.point = setter(prevBuf, line);
	while (params.eof > 0 && !params.point)
	{
		params.eof = read(fd, params.buf, 10);
		if (params.eof <= 0)
			return (to_return (*line, &prevBuf, params.eof, params.buf));
		params.buf[params.eof] = '\0';
		params.point = ft_strchr(params.buf, '\n');
		if (params.point)
			prevBuf = change(&params.point, &prevBuf);
		params.for_free = *line;
		*line = ft_strjoin(*line, params.buf);
		free (params.for_free);
	}
	return (to_return(*line, &prevBuf, params.eof, params.buf));
}
