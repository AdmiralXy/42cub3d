/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strs_push_front.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:22:00 by kricky            #+#    #+#             */
/*   Updated: 2021/11/19 22:55:00 by kricky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strs_push_front(char **strs, const char *str)
{
	int		i;
	int		j;
	char	**result;

	result = malloc(sizeof(char *) * (ft_strslen(strs) + 2));
	if (!result)
		return (0);
	i = 0;
	j = 0;
	result[j++] = ft_strdup(str);
	while (strs[i])
	{
		result[j++] = ft_strdup(strs[i]);
		i++;
	}
	result[j] = 0;
	return (result);
}
