/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:22:00 by kricky            #+#    #+#             */
/*   Updated: 2021/11/19 22:55:00 by kricky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (!s || !len)
		return (ft_strdup(""));
	i = 0;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	if (start < ft_strlen(s))
	{
		while (s[i + start] != '\0' && i < len)
		{
			str[i] = s[i + start];
			i++;
		}
	}
	str[i] = '\0';
	return (str);
}
