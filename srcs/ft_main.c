#include "ft_cub3d.h"

int	main(int argc, char **argv)
{
	t_env	*env;

	if (argc == 2)
	{
		//ft_putstr_fd("error: cub3d: please specify the path to the map!\n", 1);
		exit(1);
	}
	(void)argv;
	env = malloc(sizeof(t_env));
	//env->map_name = ft_strdup(argv[1]);
	env->map_name = ft_strdup("map.cub");
	 if (!ft_initialize(env))
	 	return (1);
//	get_path(env);
//	rewrite_map(env);
	 if (!ft_parser(env))
	 	return (1);
	 ft_initialize_graphics(env);
	 ft_minimap(env);
	 ft_raycasting(env);
	 mlx_loop(env->mlx);
	return (0);
}
