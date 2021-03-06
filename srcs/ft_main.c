/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faggar <faggar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 18:08:38 by kricky            #+#    #+#             */
/*   Updated: 2021/12/11 15:35:40 by faggar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	check_point_cub_xpm(char *a, int i, t_env *env)
{
	char	*dst;
	int		oh;
	int		uh;

	oh = 0;
	uh = 0;
	if (i == 1)
		dst = ft_strdup(".cub");
	else
	{
		dst = ft_strdup(".xpm");
		while (a[oh] != 'x')
			oh++;
		oh--;
	}
	while (!dst || !a)
		my_exit(1, env);
	while (a[oh])
	{
		if (a[oh++] == dst[uh++])
			;
		else
			my_exit(1, env);
	}
	free(dst);
}

void	check_cub(char **av, t_env *env)
{
	int		i;
	int		j;
	int		start;
	int		len;
	char	*a;

	a = NULL;
	i = 1;
	j = 0;
	start = 0;
	len = 0;
	while (av[i][j] != '.')
		j++;
	start = j;
	while (av[i][j] != '\0')
		j++;
	len = j - start;
	a = ft_substr(av[i], start, len);
	check_point_cub_xpm(a, 1, env);
	free(a);
}

int	main(int argc, char **argv)
{
	t_env	*env;

	if (argc != 2)
	{
		ft_error();
		exit(1);
	}
	env = malloc(sizeof(t_env));
	env->map_name = ft_strdup(argv[1]);
	if (!ft_valid_file(env))
	{
		ft_error();
		return (1);
	}
	if (!ft_initialize(env))
		return (1);
	get_path(env);
	rewrite_map(env);
	check_cub(argv, env);
	ft_initialize_graphics(env);
	ft_minimap(env);
	ft_raycasting(env);
	mlx_loop(env->mlx);
	free(env->map_name);
	free(env);
}
