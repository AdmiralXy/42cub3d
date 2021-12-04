#include "ft_cub3d.h"

// TODO Collision for world width/height

int	ft_move_forward(t_env *env)
{
	int		x_step;
	int		y_step;
	double	old_pos_x;
	double	old_pos_y;

	x_step = (int)(env->p.pos_x + env->p.dir_x * env->p.move_speed);
	y_step = (int)(env->p.pos_y + env->p.dir_y * env->p.move_speed);
	old_pos_x = env->p.pos_x;
	old_pos_y = env->p.pos_y;
	if (x_step <= env->world_height && y_step <= env->world_width
		&& x_step > 0 && y_step > 0)
	{
		if (env->world_map[x_step][(int)(env->p.pos_y)] == 0)
			env->p.pos_x += env->p.dir_x * env->p.move_speed;
		if (env->world_map[(int)(env->p.pos_x)][y_step] == 0)
			env->p.pos_y += env->p.dir_y * env->p.move_speed;
		if (old_pos_x == env->p.pos_x && old_pos_y == env->p.pos_y)
			return (0);
		return (1);
	}
	return (0);
}

int	ft_move_back(t_env *env)
{
	int		x_step;
	int		y_step;
	double	old_pos_x;
	double	old_pos_y;

	x_step = (int)(env->p.pos_x - env->p.dir_x * env->p.move_speed);
	y_step = (int)(env->p.pos_y - env->p.dir_y * env->p.move_speed);
	old_pos_x = env->p.pos_x;
	old_pos_y = env->p.pos_y;
	if (x_step <= env->world_height && y_step <= env->world_width
		&& x_step > 0 && y_step > 0)
	{
		if (env->world_map[x_step][(int)(env->p.pos_y)] == 0)
			env->p.pos_x -= env->p.dir_x * env->p.move_speed;
		if (env->world_map[(int)(env->p.pos_x)][y_step] == 0)
			env->p.pos_y -= env->p.dir_y * env->p.move_speed;
		if (old_pos_x == env->p.pos_x && old_pos_y == env->p.pos_y)
			return (0);
		return (1);
	}
	return (0);
}

int	ft_move_left(t_env *env)
{
	int		x_step;
	int		y_step;
	double	old_pos_x;
	double	old_pos_y;

	x_step = (int)(env->p.pos_x - env->p.plane_x * env->p.move_speed);
	y_step = (int)(env->p.pos_y - env->p.plane_y * env->p.move_speed);
	old_pos_x = env->p.pos_x;
	old_pos_y = env->p.pos_y;
	if (x_step <= env->world_height && y_step <= env->world_width
		&& x_step > 0 && y_step > 0)
	{
		if (env->world_map[x_step][(int)(env->p.pos_y)] == 0)
			env->p.pos_x -= env->p.plane_x * env->p.move_speed;
		if (env->world_map[(int)(env->p.pos_x)][y_step] == 0)
			env->p.pos_y -= env->p.plane_y * env->p.move_speed;
		if (old_pos_x == env->p.pos_x && old_pos_y == env->p.pos_y)
			return (0);
		return (1);
	}
	return (0);
}

int	ft_move_right(t_env *env)
{
	int		x_step;
	int		y_step;
	double	old_pos_x;
	double	old_pos_y;

	x_step = (int)(env->p.pos_x + env->p.plane_x * env->p.move_speed);
	y_step = (int)(env->p.pos_y + env->p.plane_y * env->p.move_speed);
	old_pos_x = env->p.pos_x;
	old_pos_y = env->p.pos_y;
	if (x_step <= env->world_height && y_step <= env->world_width
		&& x_step > 0 && y_step > 0)
	{
		if (env->world_map[x_step][(int)(env->p.pos_y)] == 0)
			env->p.pos_x += env->p.plane_x * env->p.move_speed;
		if (env->world_map[(int)(env->p.pos_x)][y_step] == 0)
			env->p.pos_y += env->p.plane_y * env->p.move_speed;
		if (old_pos_x == env->p.pos_x && old_pos_y == env->p.pos_y)
			return (0);
		return (1);
	}
	return (0);
}
