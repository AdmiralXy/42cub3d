/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting_rays.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 18:08:38 by kricky            #+#    #+#             */
/*   Updated: 2021/12/05 18:08:48 by kricky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	ft_calculate_steps(t_env *env, t_raycasting *rcs)
{
	if (rcs->ray_dir_x < 0)
	{
		rcs->step_x = -1;
		rcs->side_dist_x
			= (env->p.pos_x - rcs->map_x) * rcs->delta_dist_x;
	}
	else
	{
		rcs->step_x = 1;
		rcs->side_dist_x
			= (rcs->map_x + 1.0 - env->p.pos_x) * rcs->delta_dist_x;
	}
	if (rcs->ray_dir_y < 0)
	{
		rcs->step_y = -1;
		rcs->side_dist_y
			= (env->p.pos_y - rcs->map_y) * rcs->delta_dist_y;
	}
	else
	{
		rcs->step_y = 1;
		rcs->side_dist_y
			= (rcs->map_y + 1.0 - env->p.pos_y) * rcs->delta_dist_y;
	}
}

void	ft_calculate_rays(t_env *env, t_raycasting *rcs)
{
	while (rcs->hit == 0)
	{
		if (rcs->side_dist_x < rcs->side_dist_y)
		{
			rcs->side_dist_x += rcs->delta_dist_x;
			rcs->map_x += rcs->step_x;
			rcs->side = 0;
		}
		else
		{
			rcs->side_dist_y += rcs->delta_dist_y;
			rcs->map_y += rcs->step_y;
			rcs->side = 1;
		}
		if (env->world_map[rcs->map_x][rcs->map_y] > 0)
			rcs->hit = 1;
	}
}

void	ft_init_ray(t_env *env, t_raycasting *rcs, int x)
{
	rcs->camera_x = 2 * x / (double) WIN_WIDTH - 1;
	rcs->ray_dir_x = env->p.dir_x + env->p.plane_x * rcs->camera_x;
	rcs->ray_dir_y = env->p.dir_y + env->p.plane_y * rcs->camera_x;
	rcs->map_x = (int) env->p.pos_x;
	rcs->map_y = (int) env->p.pos_y;
	if (rcs->ray_dir_x == 0)
		rcs->delta_dist_x = 77028;
	else
		rcs->delta_dist_x = fabs(1 / rcs->ray_dir_x);
	if (rcs->ray_dir_y == 0)
		rcs->delta_dist_y = 77028;
	else
		rcs->delta_dist_y = fabs(1 / rcs->ray_dir_y);
	rcs->hit = 0;
	ft_calculate_steps(env, rcs);
	ft_calculate_rays(env, rcs);
}
