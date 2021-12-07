#include "ft_cub3d.h"

void write_map(t_env *env)
{
	int cnt;
	int k;
	cnt = 0;
	while (cnt < env->world_height)
	{
		k = 0;
		while (k < env->world_width)
		{
			printf("%d", env->world_map[cnt][k]);
			k++;
		}
		puts("");
		cnt++;
	}
}
int	main(int ac, char **av)
{
	t_env	*env;

	if (ac == 2)
	{
		ft_error("please specify the path to the map!");
		exit(1);
	}
	(void)av;
	env = malloc(sizeof(t_env));
	//env->map_name = ft_strdup(argv[1]);
	env->map_name = ft_strdup("new.cub");
	if (!ft_initialize(env))
		return (1);
	get_path(env);
	rewrite_map(env);
	write_map(env);
	//printf("map: %d\n", env->world_map[8][3]);
	//  if (!ft_parser(env))
	//  	return (1);
	ft_initialize_graphics(env);
	ft_minimap(env);
	ft_raycasting(env);
	mlx_loop(env->mlx);
	free(env->map_name);
	free(env);
}
