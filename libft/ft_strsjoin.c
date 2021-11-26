/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:22:00 by kricky            #+#    #+#             */
/*   Updated: 2021/11/19 22:55:00 by kricky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsjoin(char **strs1, char **strs2)
{
	int		n;
	int		i;
	int		j;
	char	**result;

	n = ft_strslen(strs1) + ft_strslen(strs2);
	result = malloc(sizeof(char *) * (n + 1));
	if (!result)
		return (0);
	i = 0;
	j = 0;
	while (strs1[j])
		result[i++] = ft_strdup(strs1[j++]);
	j = 0;
	while (strs2[j])
		result[i++] = ft_strdup(strs2[j++]);
	result[i] = 0;
	return (result);
}
