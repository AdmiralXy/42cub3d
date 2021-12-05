#include "ft_cub3d.h"

int	check_line(char *line)
{
	line = ft_strtrim(line, " ");
	line = ft_strtrim(line, "\t");
	if (line[0] != '\0')
		return (1);
	return (-1);
}

int	get_height(t_env *env)
{
	int		cnt;
	int		tmp;
	char	*line;
	int		flag;

	cnt = 0;
	while (get_next_line(env->fd, &line))
	{
		env->strs++;
		if (check_line(line) == 1)
			break;
	}
	flag = 0;
	while (get_next_line(env->fd, &line))
	{
		tmp = ft_strlen(line);
		if (env->world_width < tmp)
			env->world_width = tmp;
		if (check_line(line) == -1)
		{
			flag = 1;
			break;
		}
		cnt++;
	}
	if (flag == 1)
	{
		while (get_next_line(env->fd, &line))
		{
			if (check_line(line) == 1)
				my_exit(2, env);
		}
		if (check_line(line) == 1)
			my_exit(2, env);
	}
	else
	{
		if (check_line(line) == 1)
			cnt++;
	}
	close(env->fd);

	return (cnt + 1);
}

int	validate_symb(char c)
{
	if (c == ' ')
		return (SPACE);
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
int get_cur_str(t_env *env)
{
	int		i;
	char	*line;

	i = 0;
	env->fd = open(env->map_name, O_RDONLY, 0);
	while (++i < env->strs)
		get_next_line(env->fd, &line);
	return 1;
}