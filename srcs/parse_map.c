/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faggar <faggar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 18:03:32 by faggar            #+#    #+#             */
/*   Updated: 2021/12/07 15:34:52 by faggar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	check_first_end(t_env *env, char *line, int number)
{
	int		cnt;
	char	a;

	cnt = 0;
	while (line[cnt] != 0)
	{
		a = line[cnt];
		if (a != '1' && a != ' ' && a != '\t')
			my_exit(2, env);
		cnt++;
	}
	fill_int_array(env, line, number);
}

void	check_middle(t_env *env, char *line, int number)
{
	int		cnt;
	int		tmp;

	cnt = 0;
	if (number + 1 == env->world_height)
		check_first_end(env, line, number);
	else
	{
		while (line[cnt] != 0)
		{
			tmp = validate_symb(line[cnt]);
			if (tmp == -1)
				my_exit(2, env);
			cnt++;
		}
		fill_int_array(env, line, number);
	}
}

int	write_array_par(t_env *env)
{
	char	*line;
	int		cnt;

	cnt = 0;
	get_next_line(env->fd, &line);
	check_first_end(env, line, cnt++);
	free(line);
	while (cnt < env->world_height)
	{
		get_next_line(env->fd, &line);
		check_middle(env, line, cnt);
		free(line);
		cnt++;
	}
	return (1);
}

void	malloc_arrays(t_env *env)
{
	int	cnt;

	env->world_map = (int **)malloc(sizeof(int *) * env->world_height);
	if (!env->world_map)
		my_exit(4, env);
	cnt = -1;
	while (++cnt < env->world_height)
	{
		env->world_map[cnt] = malloc(sizeof(int) * env->world_width);
		if (!env->world_map[cnt])
			my_exit(4, env);
	}
}

int	rewrite_map(t_env *env)
{
	env->player = 0;
	env->world_width = 0;
	env->world_height = get_height(env);
	malloc_arrays(env);
	get_cur_str(env);
	write_array_par(env);
	finish_map_parser(env);
	return (1);
}
