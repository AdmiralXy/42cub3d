#include "ft_cub3d.h"

void ft_clear_world(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->world_height)
	{
		free(env->world_map[i]);
		i++;
	}
	free(env->world_map);
}

void ft_clear_textures(t_env *env)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		mlx_destroy_image(env->mlx, env->textures[i]->image);
		free(env->textures[i]);
		i++;
	}
	free(env->textures);
}

int	ft_exit(t_env *env)
{
	ft_clear_textures(env);
	ft_clear_world(env);
	mlx_destroy_image(env->mlx, env->img_ptr);
	mlx_clear_window(env->mlx, env->mlx_win);
	mlx_destroy_window(env->mlx, env->mlx_win);
	free(env);
	exit(0);
}

void ft_drawing_test(t_env *env);
void ft_draw(t_env *env);

int	ft_key_mlx(int keycode, t_env *env)
{
	int redraw;

	redraw = 0;
	printf("Pressed: %d\n", keycode);
	if (keycode == KEY_EXIT)
		ft_exit(env);
	if (keycode == KEY_UP)
		redraw |= ft_move_forward(env);
	if (keycode == KEY_LEFT)
		redraw |= ft_camera_left(env, env->p.rotation_speed);
	if (keycode == KEY_DOWN)
		redraw |= ft_move_back(env);
	if (keycode == KEY_RIGHT)
		redraw |= ft_camera_right(env, env->p.rotation_speed);
	if (redraw)
	{
		ft_drawing_test(env);
		ft_draw(env);
	}
	return (0);
}

void	ft_initialize_keys(t_env *env)
{
	mlx_do_key_autorepeaton(env->mlx);
	mlx_hook(env->mlx_win, 17, 17, ft_exit, env);
	mlx_hook(env->mlx_win, 2, 0, ft_key_mlx, env);
	mlx_hook(env->mlx_win, 3, 0, ft_key_mlx, env);
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
	// initial speed
	env->p.move_speed = 0.45;
	env->p.rotation_speed = 0.07;
	// initial direction vector
	env->p.dir_x = -1;
	env->p.dir_y = 0;
	// the 2d raycaster version of camera plane
	env->p.plane_x = 0;
	env->p.plane_y = 0.66;
	// rotate player
	if (env->p.direction == NORTH)
		ft_camera_left(env, 3.15);
	if (env->p.direction == EAST)
		ft_camera_right(env, 1.55);
	return (1);
}

int	ft_initialize(t_env *env)
{
	if (!env)
		return (0);
	if (!ft_initialize_mlx(env))
		return (0);
	ft_initialize_keys(env);
	env->textures = malloc(sizeof(t_texture *) * 8);
	if (!env->textures)
		return (0);
	return (1);
}
