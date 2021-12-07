/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faggar <faggar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 17:45:53 by faggar            #+#    #+#             */
/*   Updated: 2021/12/07 14:52:15 by faggar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

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

int	get_height(t_env *env)
{
	int		cnt;
	int		tmp;
	char	*line;
	int		flag;

	cnt = 0;
	skip_empty_lines(env, &line);
	flag = 0;
	while (get_next_line(env->fd, &line))
	{
		tmp = ft_strlen(line);
		if (env->world_width < tmp)
			env->world_width = tmp;
		if (check_line(line) == -1)
		{
			flag = 1;
			break ;
		}
		free(line);
		cnt++;
	}
	get_height_p2(env, line, &cnt, flag);
	return (cnt + 1);
}

void	fill_int_p2(t_env *env, int number, int cnt)
{
	while (cnt < env->world_width)
	{
		env->world_map[number][cnt] = -1;
		cnt++;
	}
}

void	fill_int_array(t_env *env, char *line, int number)
{
	int	cnt;
	int	tmp;

	cnt = 0;
	while (line[cnt] != 0)
	{
		tmp = validate_symb(line[cnt]);
		if (tmp == SPACE)
			env->world_map[number][cnt] = -1;
		else if (tmp == SYMB_ONE)
			env->world_map[number][cnt] = 1;
		else if (tmp == SYMB_ZERO)
			env->world_map[number][cnt] = 0;
		else if (tmp >= PLAYER_NORTH && tmp <= PLAYER_WEST)
		{
			if (env->player != 0)
				my_exit(3, env);
			env->world_map[number][cnt] = 0;
			env->p.pos_x = number;
			env->p.pos_y = cnt;
			env->player = 1;
			env->p.initial_direction = tmp - 11;
		}
		cnt++;
	}
	fill_int_p2(env, number, cnt);
}
