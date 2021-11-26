/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strssort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:22:00 by kricky            #+#    #+#             */
/*   Updated: 2021/11/19 22:55:00 by kricky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strssort(char **strs)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (strs[i])
	{
		j = 0;
		while (strs[j])
		{
			if (ft_strcmp(strs[i], strs[j]) < 0)
			{
				temp = strs[i];
				strs[i] = strs[j];
				strs[j] = temp;
			}
			j++;
		}
		i++;
	}
}
