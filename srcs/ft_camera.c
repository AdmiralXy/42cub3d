#include "ft_cub3d.h"

int	ft_camera_left(t_env *env, double angle)
{
	double	oldDirX;
	double	oldPlaneX;

	oldDirX = env->p.dir_x;
	oldPlaneX = env->p.plane_x;
	env->p.dir_x = env->p.dir_x * cos(angle) - env->p.dir_y * sin(angle);
	env->p.dir_y = oldDirX * sin(angle) + env->p.dir_y * cos(angle);
	env->p.plane_x = env->p.plane_x * cos(angle) - env->p.plane_y * sin(angle);
	env->p.plane_y = oldPlaneX * sin(angle) + env->p.plane_y * cos(angle);
	return (1);
}

int	ft_camera_right(t_env *env, double angle)
{
	double	oldDirX;
	double	oldPlaneX;

	oldDirX = env->p.dir_x;
	oldPlaneX = env->p.plane_x;
	env->p.dir_x = env->p.dir_x * cos(-angle) - env->p.dir_y * sin(-angle);
	env->p.dir_y = oldDirX * sin(-angle) + env->p.dir_y * cos(-angle);
	env->p.plane_x = env->p.plane_x * cos(-angle) - env->p.plane_y * sin(-angle);
	env->p.plane_y = oldPlaneX * sin(-angle) + env->p.plane_y * cos(-angle);
	return (1);
}
