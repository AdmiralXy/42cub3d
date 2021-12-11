/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faggar <faggar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 14:48:04 by faggar            #+#    #+#             */
/*   Updated: 2021/12/11 15:37:09 by faggar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int	checkkkk(t_env *env, int side, char *line)
{
	if (side == FLOOR || side == CEIL)
	{
		fill_floor_ceil(env, line, side);
		free (line);
		return (10);
	}
	return (1);
}

void	player(t_env *env, int number, int arr_cnt, int tmp)
{
	if (env->player != 0)
		my_exit(3, env);
	env->world_map[number][arr_cnt] = 0;
	env->p.pos_x = number + 0.5;
	env->p.pos_y = arr_cnt + 0.5;
	env->player = 1;
	env->p.initial_direction = tmp - 11;
}

void	get_height_p2(t_env *env, char *line, int *cnt, int flag)
{
	if (flag == 1)
	{
		while (get_next_line(env->fd, &line))
		{
			if (check_line(line) == 1)
			{
				free(line);
				my_exit(2, env);
			}
			free(line);
		}
		if (check_line(line) == 1)
		{
			free(line);
			my_exit(2, env);
		}
	}
	else
	{
		if (check_line(line) == 1)
			(*cnt)++;
	}
	free(line);
	close(env->fd);
}

void	skip_empty_lines(t_env *env, char **line)
{
	while (get_next_line(env->fd, line))
	{
		env->strs++;
		if (check_line(*line) == 1)
		{
			free(*line);
			break ;
		}
		free(*line);
	}
}

int	ft_valid_file(t_env *env)
{
	char	*line;
	int		fd;

	line = 0;
	fd = open(env->map_name, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
		free(line);
	close(fd);
	if (line)
		free(line);
	else
	{
		free(env->map_name);
		free(env);
		return (0);
	}
	return (1);
}
