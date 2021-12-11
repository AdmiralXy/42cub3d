/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faggar <faggar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 18:07:23 by faggar            #+#    #+#             */
/*   Updated: 2021/12/11 14:49:28 by faggar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int	choose_side(t_env *env, char *line)
{
	if (line[0] == 'S' && line[1] == 'O')
		return (SOUTH);
	else if (line[0] == 'W' && line[1] == 'E')
		return (WEST);
	else if (line[0] == 'N' && line[1] == 'O')
		return (NORTH);
	else if (line[0] == 'E' && line[1] == 'A')
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
	if (checkkkk(env, side, line) == 10)
		return (10);
	if (env->swne_path[side][0] != '\0')
		my_exit(1, env);
	cnt += 2;
	while (line[cnt] == ' ' || line[cnt] == '\t')
		cnt++;
	if (line[cnt] != '.')
		my_exit(1, env);
	free(env->swne_path[side]);
	env->swne_path[side] = ft_strdup(line + cnt);
	free(line);
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
		get_pic_path(env, env->fd);
		cnt++;
	}
	env->textures[NORTH] = ft_get_texture(env, env->swne_path[NORTH]);
	env->textures[SOUTH] = ft_get_texture(env, env->swne_path[SOUTH]);
	env->textures[EAST] = ft_get_texture(env, env->swne_path[EAST]);
	env->textures[WEST] = ft_get_texture(env, env->swne_path[WEST]);
	return (valid_checker(env));
}
