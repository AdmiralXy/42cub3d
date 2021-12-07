/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_map_parser_helper.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faggar <faggar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 17:55:08 by faggar            #+#    #+#             */
/*   Updated: 2021/12/07 16:58:04 by faggar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	check_first_last_str(t_env *env, int number)
{
	int	cnt;

	cnt = 0;
	if (number == 0)
	{
		while (cnt < env->world_width)
		{
			if (env->world_map[number][cnt] == 0)
				my_exit (2, env);
			cnt++;
		}
	}
}
void	better_check_vertical(t_env *env, int number, int cnt)
{
	int	vertical;
	int k;

	vertical = 1;
	for (int i = 0; i < env->world_height; i++)
	{
		for (int s = 0; s < env->world_width; s++)
			printf("%d ", env->world_map[i][s]);
		puts("");
	}
	while (env->world_map[number - vertical][cnt] != 1)
	{
		k = env->world_map[number - vertical][cnt+1];
		if (number - vertical == 0
			&& env->world_map[number - vertical][cnt] != 1)
			my_exit(2, env);
		if (env->world_map[number - vertical][cnt] == -1)
			my_exit(2, env);
		vertical++;
	}
	vertical = 1;
	while (env->world_map[number + vertical][cnt] != 1)
	{
		if (number + vertical == env->world_height
			&& env->world_map[number + vertical][cnt] != 1)
			my_exit(2, env);
		if (env->world_map[number + vertical][cnt] == -1)
			my_exit(2, env);
		vertical++;
	}
}

void	better_check_horizontal(t_env *env, int number, int cnt)
{
	int	horizontal;

	horizontal = 1;
	while (env->world_map[number][cnt + horizontal] != 1)
	{
		if (cnt + horizontal == env->world_width
			&& env->world_map[number][cnt + horizontal] != 1)
			my_exit(2, env);
		if (env->world_map[number][cnt + horizontal] == -1)
			my_exit(2, env);
		horizontal++;
	}
	horizontal = 1;
	while (env->world_map[number][cnt - horizontal] != 1)
	{
		if (cnt - horizontal == 0
			&& env->world_map[number][cnt + horizontal] != 1)
			my_exit(2, env);
		if (env->world_map[number][cnt - horizontal] == -1)
			my_exit(2, env);
		horizontal++;
	}
}
