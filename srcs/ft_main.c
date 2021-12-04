#include "ft_cub3d.h"

int	main(int ac, char **av)
{
	t_env	*env;

	if (ac == 2)
		exit(1);
	(void)av;
	env = malloc(sizeof(t_env));
	env->map_name = ft_strdup("map.cub");
	// if (!ft_initialize(env))
	// 	return (1);
	get_path(env);
	puts(env->swne_path[NORTH]);
	// if (!ft_parser(env))
	// 	return (1);
	// ft_initialize_graphics(env);
	// ft_minimap(env);
	// ft_raycasting(env);
	// mlx_loop(env->mlx);
	return (0);
}
