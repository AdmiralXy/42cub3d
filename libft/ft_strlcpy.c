/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:22:00 by kricky            #+#    #+#             */
/*   Updated: 2021/11/19 22:55:00 by kricky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	temp;

	i = 0;
	temp = 0;
	if (dst && src)
	{
		while (src[temp] != '\0')
			temp++;
		while (src[i] != '\0' && i + 1 < dstsize)
		{
			dst[i] = src[i];
			i++;
		}
		if (dstsize != 0)
			dst[i] = '\0';
	}
	return (temp);
}
