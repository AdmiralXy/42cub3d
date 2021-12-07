#include "ft_cub3d.h"

int	main(int argc, char **argv)
{
	t_env	*env;

	if (argc != 2)
	{
		ft_error("usage ./cub3d [path_to_the_map]");
		exit(1);
	}
	env = malloc(sizeof(t_env));
	env->map_name = ft_strdup(argv[1]);
	if (!ft_initialize(env))
		return (1);
	get_path(env);
	rewrite_map(env);
	ft_initialize_graphics(env);
	ft_minimap(env);
	ft_raycasting(env);
	mlx_loop(env->mlx);
	free(env->map_name);
	free(env);
}
