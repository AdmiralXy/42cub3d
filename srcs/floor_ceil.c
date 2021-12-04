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

int	fill_floor_ceil(t_env *env, char *line, int f_or_c)
{
	char 	**splt;
	int		cnt;
	int		checker;

	cnt = 0;
	splt = ft_split(line + 1, ',');
	if (splt[0] == NULL || splt[1] == NULL
		|| splt[2] == NULL || splt[3] != NULL)
		my_exit(1, env);
	while (splt[cnt] != NULL)
	{
		splt[cnt] = ft_strtrim(splt[cnt], " ");
		splt[cnt] = ft_strtrim(splt[cnt], "\t");
		checker = check_str(splt[cnt]);
		if (checker == -1)
			my_exit(1, env);
		cnt++;
	}
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
	return (1);
}