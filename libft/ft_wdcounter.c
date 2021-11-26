/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wdcounter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:22:00 by kricky            #+#    #+#             */
/*   Updated: 2021/11/19 22:55:00 by kricky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_wdcounter(const char *str, char separator)
{
	int	i;
	int	finded;
	int	counter;

	i = 0;
	finded = 0;
	counter = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && finded == 0 && ++counter)
			finded = 1;
		else if (str[i] == separator)
			finded = 0;
		i++;
	}
	return (counter);
}
