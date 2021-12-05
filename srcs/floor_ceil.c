/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceil.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faggar <faggar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 19:47:18 by faggar            #+#    #+#             */
/*   Updated: 2021/12/05 19:48:20 by faggar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

static int	check_str(char *str)
{
	int	cnt;

	cnt = 0;
	while (str[cnt] != '\0')
	{
		if (!ft_isdigit(str[cnt]))
			return (-1);
		cnt++;
	}
	cnt = ft_atoi(str);
	if (cnt < -1 && cnt > 255)
		return (-1);
	return (cnt);
}

void	fill_floor_ceil_p2(t_env *env, int f_or_c, char **splt)
{
	if (f_or_c == FLOOR)
	{
		env->floor_color = ft_rgb_to_hex(ft_atoi(splt[0]), ft_atoi(splt[1]),
				ft_atoi(splt[2]));
	}
	else
	{
		env->ceil_color = ft_rgb_to_hex(ft_atoi(splt[0]), ft_atoi(splt[1]),
				ft_atoi(splt[2]));
	}
	f_or_c = -1;
	while (splt[++f_or_c] != NULL)
		free(splt[f_or_c]);
	free(splt);
}

int	fill_floor_ceil(t_env *env, char *line, int f_or_c)
{
	char	**splt;
	int		cnt;
	int		checker;
	char	*tmp;

	cnt = 0;
	splt = ft_split(line + 1, ',');
	if (splt[0] == NULL || splt[1] == NULL
		|| splt[2] == NULL || splt[3] != NULL)
		my_exit(1, env);
	while (splt[cnt] != NULL)
	{
		tmp = ft_strtrim(splt[cnt], " ");
		free(splt[cnt]);
		splt[cnt] = ft_strtrim(tmp, "\t");
		free(tmp);
		checker = check_str(splt[cnt]);
		if (checker == -1)
			my_exit(1, env);
		cnt++;
	}
	fill_floor_ceil_p2(env, f_or_c, splt);
	return (1);
}
