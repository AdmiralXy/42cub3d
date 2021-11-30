/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faggar <faggar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 19:32:43 by faggar            #+#    #+#             */
/*   Updated: 2021/09/16 19:32:55 by faggar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include	<stdio.h>
# include	<fcntl.h>
# include	<stdlib.h>
# include	<unistd.h>
# include	<string.h>

typedef struct s_gnl
{
	int			eof;
	char		*for_free;
	char		*point;
	char		*buf;
}				t_gnl;

int		get_next_line(int fd, char **line);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *s);
void	ft_strcpy(char *dst, const char *src);

#endif