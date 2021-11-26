/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:22:00 by kricky            #+#    #+#             */
/*   Updated: 2021/11/19 22:55:00 by kricky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_str_replace(char **str, const char *rep, const char *in, int start)
{
	int		i;
	char	*temp1;
	char	*temp2;
	char	*e_ptr;
	char	*input;

	input = *str;
	i = 0;
	e_ptr = ft_strnstr(input + start, rep, ft_strlen(input));
	while (e_ptr && &input[i] != e_ptr)
		i++;
	temp2 = ft_substr(input, 0, i);
	temp1 = ft_strjoin(temp2, in);
	free(temp2);
	temp2 = ft_strjoin(temp1, input + i + ft_strlen(rep));
	free(temp1);
	free(input);
	*str = temp2;
}
