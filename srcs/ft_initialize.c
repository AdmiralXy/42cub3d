#include "ft_cub3d.h"

void ft_clear_world(void)
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

void ft_clear_textures(void)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free(env->textures[i]);
		i++;
	}
	free(env->textures);
}

int	ft_exit(void *data)
{
	(void)data;
	ft_clear_textures();
	ft_clear_world();
	mlx_destroy_image(env->mlx, env->img_ptr);
	mlx_clear_window(env->mlx, env->mlx_win);
	mlx_destroy_window(env->mlx, env->mlx_win);
	free(env);
	exit(0);
}

int	ft_key_up(void *data)
{
	double moveSpeed = 0.45;

	// move forward if no wall in front of you
	int x_step = (int) (posX + dirX * moveSpeed);
	int y_step = (int) (posY + dirY * moveSpeed);
	if (x_step <= 24 && y_step <= 24 && x_step > 0 && y_step > 0)
	{
		if(env->world_map[x_step][(int)(posY)] == 0) posX += dirX * moveSpeed;
		if(env->world_map[(int)(posX)][y_step] == 0) posY += dirY * moveSpeed;
		return (1);
	}
	(void)data;
	return (0);
}

int	ft_key_left(void *data)
{
	double rotSpeed = 0.07;
	// both camera direction and camera plane must be rotated
	double oldDirX = dirX;
	dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
	dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
	double oldPlaneX = planeX;
	planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
	planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
	(void)data;
	return (1);
}

int	ft_key_down(void *data)
{
	double moveSpeed = 0.45;

	int x_step = (int) (posX - dirX * moveSpeed);
	int y_step = (int) (posY - dirY * moveSpeed);
	if (x_step <= 24 && y_step <= 24 && x_step > 0 && y_step > 0)
	{
		if(env->world_map[x_step][(int)(posY)] == 0) posX -= dirX * moveSpeed;
		if(env->world_map[(int)(posX)][y_step] == 0) posY -= dirY * moveSpeed;
		return (1);
	}
	(void)data;
	return (0);
}

int	ft_key_right(void *data)
{
	double rotSpeed = 0.07;

	//both camera direction and camera plane must be rotated
	double oldDirX = dirX;
	dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
	dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
	double oldPlaneX = planeX;
	planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
	planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
	(void)data;
	return (1);
}

void ft_drawing_test();
void ft_draw();

int	ft_key_mlx(int keycode, void *data)
{
	int redraw;

	redraw = 0;
	(void)data;
	printf("Pressed: %d\n", keycode);
	if (keycode == KEY_EXIT)
		ft_exit(NULL);
	if (keycode == KEY_UP)
		redraw |= ft_key_up(NULL);
	if (keycode == KEY_LEFT)
		redraw |= ft_key_left(NULL);
	if (keycode == KEY_DOWN)
		redraw |= ft_key_down(NULL);
	if (keycode == KEY_RIGHT)
		redraw |= ft_key_right(NULL);
	if (redraw)
	{
		ft_drawing_test();
		ft_draw();
	}
	return (0);
}

void	ft_initialize_keys(void)
{
	mlx_do_key_autorepeaton(env->mlx);
	mlx_hook(env->mlx_win, 17, 17, ft_exit, NULL);
	mlx_hook(env->mlx_win, 2, 0, ft_key_mlx, NULL);
	mlx_hook(env->mlx_win, 3, 0, ft_key_mlx, NULL);
	//mlx_key_hook(env->mlx_win, ft_key_mlx, NULL);
}

int	ft_initialize(void)
{
	env = malloc(sizeof(t_env));
	if (!env)
		return (0);
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
	ft_initialize_keys();
	env->textures = malloc(sizeof(int *) * 4);
	if (!env->textures)
		return (0);
	return (1);
}
