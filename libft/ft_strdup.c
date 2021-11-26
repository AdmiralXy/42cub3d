/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:22:00 by kricky            #+#    #+#             */
/*   Updated: 2021/11/19 22:55:00 by kricky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
