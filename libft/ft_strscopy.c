/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strscopy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:22:00 by kricky            #+#    #+#             */
/*   Updated: 2021/11/19 22:55:00 by kricky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strscopy(char **strs)
{
	int		strs_n;
	int		i;
	char	**result;

	strs_n = 0;
	while (strs[strs_n])
		strs_n++;
	result = malloc(sizeof(char *) * (strs_n + 1));
	if (!result)
		return (0);
	i = 0;
	while (strs[i])
	{
		result[i] = ft_strdup(strs[i]);
		i++;
	}
	result[i] = 0;
	return (result);
}
