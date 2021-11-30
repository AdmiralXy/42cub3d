#include "ft_cub3d.h"

void	ft_clear_world(t_env *env)
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

void	ft_clear_textures(t_env *env)
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
