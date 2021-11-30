/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faggar <faggar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 19:37:47 by faggar            #+#    #+#             */
/*   Updated: 2021/08/13 14:07:47 by faggar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../fdf.h"

char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	*wer;

	wer = (char *)str;
	i = 0;
	while (*wer)
	{
		if (*wer == (unsigned char)c)
			return (wer);
		wer++;
	}
	if (*wer == (unsigned char)c)
		return (wer);
	return (NULL);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*wer;

	i = 0;
	while (s1[i])
		i++;
	wer = (char *)malloc((i + 1) * sizeof(char));
	if (!(wer))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		wer[i] = s1[i];
		i++;
	}
	wer[i] = '\0';
	return (wer);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	ls3;
	char	*s3;
	size_t	olley;
	size_t	s1_len;

	if (!s1 || !s2)
		return (NULL);
	olley = 0;
	s1_len = ft_strlen(s1);
	ls3 = s1_len + ft_strlen(s2);
	s3 = (char *)malloc((ls3 + 1) * sizeof(char));
	if (!(s3))
		return (NULL);
	while (olley < s1_len)
	{
		s3[olley] = s1[olley];
		olley++;
	}
	while (olley < ls3)
	{
		s3[olley] = s2[olley - s1_len];
		olley++;
	}
	s3[olley] = '\0';
	return (s3);
}

void	ft_strcpy(char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
}
