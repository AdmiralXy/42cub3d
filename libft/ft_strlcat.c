/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:22:00 by kricky            #+#    #+#             */
/*   Updated: 2021/11/19 22:55:00 by kricky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	srcsize;

	i = 0;
	j = 0;
	srcsize = ft_strlen(src);
	while (dst[i] != '\0' && i < dstsize)
	{
		i++;
	}
	while (src[j] != '\0' && i + j + 1 < dstsize)
	{
		dst[i + j] = src[j];
		j++;
	}
	if (dstsize != 0 && i < dstsize)
		dst[i + j] = '\0';
	return (srcsize + i);
}
