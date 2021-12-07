/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 18:08:38 by kricky            #+#    #+#             */
/*   Updated: 2021/12/05 18:08:48 by kricky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int	ft_key_mlx(int keycode, t_env *env)
{
	int	redraw;

	redraw = 0;
	if (keycode == KEY_EXIT)
		ft_exit(env);
	if (keycode == KEY_UP)
		redraw |= ft_move_forward(env);
	if (keycode == KEY_LEFT)
		redraw |= ft_move_left(env);
	if (keycode == KEY_DOWN)
		redraw |= ft_move_back(env);
	if (keycode == KEY_RIGHT)
		redraw |= ft_move_right(env);
	if (keycode == ARROW_LEFT)
		redraw |= ft_camera_left(env, env->p.rotation_speed);
	if (keycode == ARROW_RIGHT)
		redraw |= ft_camera_right(env, env->p.rotation_speed);
	if (redraw)
		ft_raycasting(env);
	return (0);
}

void	ft_initialize_keys(t_env *env)
{
	mlx_do_key_autorepeaton(env->mlx);
	mlx_hook(env->mlx_win, 17, 17, ft_exit, env);
	mlx_hook(env->mlx_win, 2, 0, ft_key_mlx, env);
}

int	ft_initialize_mlx(t_env *env)
{
	env->mlx = mlx_init();
	if (!env->mlx)
		return (0);
	env->mlx_win = mlx_new_window(env->mlx, WIN_HEIGHT, WIN_WIDTH, WIN_TITLE);
	if (!env->mlx_win)
		return (0);
	env->bpp = 32;
	env->size_line = WIN_HEIGHT * 4;
	env->endian = 1;
	env->img_ptr = mlx_new_image(env->mlx, WIN_HEIGHT, WIN_WIDTH);
	if (!env->img_ptr)
		return (0);
	env->img_data = mlx_get_data_addr(env->img_ptr, &env->bpp,
			&env->size_line, &env->endian);
	if (!env->img_data)
		return (0);
	ft_bzero(env->img_data, WIN_WIDTH * WIN_HEIGHT * (env->bpp / 8));
	return (1);
}

int	ft_initialize_graphics(t_env *env)
{
	env->p.move_speed = 0.45;
	env->p.rotation_speed = 0.07;
	env->p.dir_x = -1;
	env->p.dir_y = 0;
	env->p.plane_x = 0;
	env->p.plane_y = 0.66;
	if (env->p.initial_direction == SOUTH)
		ft_camera_left(env, 3.15);
	if (env->p.initial_direction == EAST)
		ft_camera_right(env, 1.55);
	if (env->p.initial_direction == WEST)
		ft_camera_right(env, 4.75);
	return (1);
}

int	ft_initialize(t_env *env)
{
	if (!env)
		return (0);
	if (!ft_initialize_mlx(env))
		return (0);
	ft_initialize_keys(env);
	env->textures = malloc(sizeof(t_texture *) * 4);
	if (!env->textures)
		return (0);
	env->textures[NORTH] = 0;
	env->textures[SOUTH] = 0;
	env->textures[WEST] = 0;
	env->textures[EAST] = 0;
	return (1);
}
