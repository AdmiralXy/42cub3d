#include "ft_cub3d.h"

int	ft_camera_left(t_env *env, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = env->p.dir_x;
	old_plane_x = env->p.plane_x;
	env->p.dir_x = env->p.dir_x * cos(angle) - env->p.dir_y * sin(angle);
	env->p.dir_y = old_dir_x * sin(angle) + env->p.dir_y * cos(angle);
	env->p.plane_x = env->p.plane_x * cos(angle) - env->p.plane_y * sin(angle);
	env->p.plane_y = old_plane_x * sin(angle) + env->p.plane_y * cos(angle);
	return (1);
}

int	ft_camera_right(t_env *env, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = env->p.dir_x;
	old_plane_x = env->p.plane_x;
	env->p.dir_x = env->p.dir_x * cos(-angle) - env->p.dir_y * sin(-angle);
	env->p.dir_y = old_dir_x * sin(-angle) + env->p.dir_y * cos(-angle);
	env->p.plane_x = env->p.plane_x * cos(-angle)
		- env->p.plane_y * sin(-angle);
	env->p.plane_y = old_plane_x * sin(-angle) + env->p.plane_y * cos(-angle);
	return (1);
}
