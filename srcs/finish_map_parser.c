/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_map_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faggar <faggar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 17:58:12 by faggar            #+#    #+#             */
/*   Updated: 2021/12/05 18:00:58 by faggar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	check_valid(t_env *env, int number, int cnt)
{
	if (cnt == env->world_width || cnt == 0)
		my_exit(2, env);
	better_check_vertical(env, number, cnt);
	better_check_horizontal(env, number, cnt);
}

void	check_middle_str(t_env *env, int number)
{
	int	cnt;

	cnt = 0;
	while (cnt < env->world_width)
	{
		if (env->world_map[number][cnt] == 0 ||
		(env->world_map[number][cnt] >= PLAYER_NORTH
		&& env->world_map[number][cnt] <= PLAYER_WEST))
			check_valid(env, number, cnt);
		cnt++;
	}
}

void	set_zeros(t_env *env)
{
	int	i;
	int	k;

	i = 0;
	while (i < env->world_height)
	{
		k = 0;
		while (k < env->world_width)
		{
			if (env->world_map[i][k] == -1)
				env->world_map[i][k] = 0;
			k++;
		}
		i++;
	}
}

int	finish_map_parser(t_env *env)
{
	int	cnt;

	cnt = 1;
	if (env->player == 0)
		my_exit(2, env);
	check_first_last_str(env, 0);
	while (cnt < env->world_height)
	{
		check_middle_str(env, cnt);
		cnt++;
	}
	set_zeros(env);
	return (1);
}
