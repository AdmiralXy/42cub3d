/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faggar <faggar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 17:45:53 by faggar            #+#    #+#             */
/*   Updated: 2021/12/11 15:00:20 by faggar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int	get_len(char *line)
{
	int	i;
	int	tabs;

	i = 0;
	tabs = 0;
	while (line[i] != 0)
	{
		if (line[i] == '\t')
			tabs++;
		i++;
	}
	return (i - tabs + tabs * 4);
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
		tmp = get_len(line);
		if (env->world_width < tmp)
			env->world_width = tmp;
		free(line);
		cnt++;
	}
	tmp = get_len(line);
	if (env->world_width < tmp)
		env->world_width = tmp;
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

void	for_tabs(int *line, int *cnt)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		line[(*cnt) + i] = -1;
		i++;
	}
	(*cnt) += 3;
}

void	fill_int_array(t_env *env, char *line, int number)
{
	int	cnt;
	int	tmp;
	int	arr_cnt;

	cnt = -1;
	arr_cnt = 0;
	while (line[++cnt] != 0)
	{
		tmp = validate_symb(line[cnt]);
		if (tmp == SPACE)
			env->world_map[number][arr_cnt] = -1;
		else if (tmp == TAB)
			for_tabs(env->world_map[number], &arr_cnt);
		else if (tmp == SYMB_ONE)
			env->world_map[number][arr_cnt] = 1;
		else if (tmp == SYMB_ZERO)
			env->world_map[number][arr_cnt] = 0;
		else if (tmp >= PLAYER_NORTH && tmp <= PLAYER_WEST)
			player(env, number, arr_cnt, tmp);
		arr_cnt++;
	}
	fill_int_p2(env, number, arr_cnt);
}
