/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faggar <faggar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 18:08:38 by kricky            #+#    #+#             */
/*   Updated: 2021/12/11 15:37:46 by faggar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	ft_error(const char *error)
{
	ft_putstr_fd("error: cub3d: ", 1);
	ft_putendl_fd((char *)error, 1);
}

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
		if (env->textures[i])
		{
			mlx_destroy_image(env->mlx, env->textures[i]->image);
			free(env->textures[i]);
		}
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
	free(env->map_name);
	free(env->mlx);
	free(env);
	exit(0);
}
