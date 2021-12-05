#include "ft_cub3d.h"

int	my_exit(int er_numb, t_env *env)
{
	if (er_numb == 1)
	{
		write(1, "bad file\n", 10);
		ft_exit(env);
	}
	if (er_numb == 2)
	{
		write(1, "bad_map\n", 9);
		ft_exit(env);
	}
	if (er_numb == 3)
	{
		write(1, "two or more players\n", 21);
		ft_exit(env);
	}
	if (er_numb == 4)
	{
		write(1, "malloc error\n", 14);
		ft_exit(env);
	}
	return (1);
}