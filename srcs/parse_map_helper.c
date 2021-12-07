/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faggar <faggar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 17:45:49 by faggar            #+#    #+#             */
/*   Updated: 2021/12/07 15:14:21 by faggar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int	check_line(char *line)
{
	int	cnt;

	cnt = -1;
	while (line[++cnt] != 0)
	{
		if (line[cnt] != ' ' && line[cnt] != '\t')
			return (1);
	}
	return (-1);
}

int	validate_symb(char c)
{
	if (c == ' ')
		return (SPACE);
	else if (c == '\t')
		return (TAB);
	else if (c == '1')
		return (SYMB_ONE);
	else if (c == '0')
		return (SYMB_ZERO);
	else if (c == 'N')
		return (PLAYER_NORTH);
	else if (c == 'S')
		return (PLAYER_SOUTH);
	else if (c == 'E')
		return (PLAYER_EAST);
	else if (c == 'W')
		return (PLAYER_WEST);
	return (-1);
}

int	get_cur_str(t_env *env)
{
	int		i;
	char	*line;

	i = 0;
	env->fd = open(env->map_name, O_RDONLY, 0);
	while (++i < env->strs)
	{
		get_next_line(env->fd, &line);
		free(line);
	}
	return (1);
}
