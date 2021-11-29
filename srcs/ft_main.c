#include "ft_cub3d.h"

int	main(void)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!ft_initialize(env))
		return (1);
	if (!ft_parser(env))
		return (1);
	ft_initialize_graphics(env);
	ft_minimap(env);
	ft_raycasting(env);
	mlx_loop(env->mlx);
	return (0);
}
