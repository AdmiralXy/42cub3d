/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faggar <faggar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 18:08:38 by faggar            #+#    #+#             */
/*   Updated: 2021/12/05 18:08:48 by faggar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int	my_exit(int er_numb, t_env *env)
{
	if (er_numb == 1)
	{
		ft_error();
		ft_exit(env);
	}
	if (er_numb == 2)
	{
		ft_error();
		ft_exit(env);
	}
	if (er_numb == 3)
	{
		ft_error();
		ft_exit(env);
	}
	if (er_numb == 4)
	{
		ft_error();
		ft_exit(env);
	}
	return (1);
}
