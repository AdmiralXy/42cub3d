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
	char	*line;

	cnt = 0;
	while (get_next_line(env->fd, &line))
	{
		env->strs++;
		if (check_line(line) == 1)
			break;
	}
	while (get_next_line(env->fd, &line))
	{
		cnt++;
	}
	close(env->fd);
	return (cnt + 1);
}
int	validate_symb(char c)
{
	if (c == ' ' || c == '1' || c == '0')
		return (1);
	else if (c == 'N' || c == 'E' || c == 'W'
	|| c == 'S')
		return (2);
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