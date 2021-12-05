/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faggar <faggar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 18:07:23 by faggar            #+#    #+#             */
/*   Updated: 2021/12/05 19:39:32 by faggar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int	choose_side(t_env *env, char *line)
{
	if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		return (SOUTH);
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		return (WEST);
	else if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		return (NORTH);
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		return (EAST);
	else if (line[0] == 'F' && line[1] == ' ')
		return (FLOOR);
	else if (line[0] == 'C' && line[1] == ' ')
		return (CEIL);
	else
		my_exit(1, env);
	return (-1);
}

void	skip_empty(t_env *env, int fd, char **line)
{
	int	cnt;

	while (get_next_line(fd, line))
	{
		env->strs++;
		cnt = -1;
		while ((*line)[++cnt] != 0)
		{
			if ((*line)[cnt] != ' ' && (*line)[cnt] != '\t')
				return ;
		}
		free(*line);
	}
}

int	get_pic_path(t_env *env, int fd)
{
	char	*line;
	int		cnt;
	int		side;

	skip_empty(env, fd, &line);
	cnt = 0;
	while (line[cnt] == ' ')
		cnt++;
	side = choose_side(env, line + cnt);
	if (side == FLOOR || side == CEIL)
	{
		fill_floor_ceil(env, line, side);
		free (line);
		return (10);
	}
	if (env->swne_path[side][0] != '\0')
		my_exit(1, env);
	while (line[cnt] != '.')
		cnt++;
	free(env->swne_path[side]);
	free(line);
	env->swne_path[side] = ft_strdup(line + cnt);
	return (side);
}

int	valid_checker(t_env *env)
{
	int	cnt;

	cnt = 0;
	while (cnt < 4)
	{
		if (env->swne_path[cnt][0] == '\0')
			my_exit(1, env);
		free(env->swne_path[cnt]);
		cnt++;
	}
	free(env->swne_path);
	if (env->ceil_color == -1 || env->floor_color == -1)
		my_exit(1, env);
	return (1);
}

int	get_path(t_env *env)
{
	int	cnt;
	int	side;

	cnt = 0;
	env->ceil_color = -1;
	env->floor_color = -1;
	env->strs = 0;
	env->fd = open(env->map_name, O_RDONLY, 0);
	env->swne_path = malloc(sizeof(char *) * 4);
	cnt = -1;
	if (env->fd == -1)
		my_exit(1, env);
	while (++cnt < 4)
		env->swne_path[cnt] = ft_calloc(1, 1);
	cnt = 0;
	while (cnt < 6)
	{
		side = get_pic_path(env, env->fd);
		cnt++;
	}
	return (valid_checker(env));
}
