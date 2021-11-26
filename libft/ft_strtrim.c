/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:22:00 by kricky            #+#    #+#             */
/*   Updated: 2021/11/19 22:55:00 by kricky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		size;
	int		i;

	i = 0;
	if (!s1 || !set)
		return (0);
	while (s1[i] != '\0' && ft_strchr(set, s1[i]))
		i++;
	size = ft_strlen(s1) - i;
	while (size != 0 && ft_strchr(set, s1[size + i]))
		size--;
	str = ft_substr(s1, i, size + 1);
	if (!str)
		return (0);
	return (str);
}
