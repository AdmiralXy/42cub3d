#include "ft_cub3d.h"

int	ft_move_forward(t_env *env)
{
	int	x_step;
	int	y_step;

	x_step = (int)(env->p.pos_x + env->p.dir_x * env->p.move_speed);
	y_step = (int)(env->p.pos_y + env->p.dir_y * env->p.move_speed);
	if (x_step <= 24 && y_step <= 24 && x_step > 0 && y_step > 0)
	{
		if (env->world_map[x_step][(int)(env->p.pos_y)] == 0)
			env->p.pos_x += env->p.dir_x * env->p.move_speed;
		if (env->world_map[(int)(env->p.pos_x)][y_step] == 0)
			env->p.pos_y += env->p.dir_y * env->p.move_speed;
		return (1);
	}
	return (0);
}

int	ft_move_back(t_env *env)
{
	int	x_step;
	int	y_step;

	x_step = (int)(env->p.pos_x - env->p.dir_x * env->p.move_speed);
	y_step = (int)(env->p.pos_y - env->p.dir_y * env->p.move_speed);
	if (x_step <= 24 && y_step <= 24 && x_step > 0 && y_step > 0)
	{
		if (env->world_map[x_step][(int)(env->p.pos_y)] == 0)
			env->p.pos_x -= env->p.dir_x * env->p.move_speed;
		if (env->world_map[(int)(env->p.pos_x)][y_step] == 0)
			env->p.pos_y -= env->p.dir_y * env->p.move_speed;
		return (1);
	}
	return (0);
}
