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
		return(FLOOR);
	else if (line[0] == 'C' && line[1] == ' ')
		return (CEIL);
	else
		my_exit(1, env);
	return (-1);
}

int	get_pic_path(t_env *env, int fd)
{
	char	*line;
	int		cnt;
	int		side;

	while (get_next_line(fd, &line))
	{
		line = ft_strtrim(line, " ");
		line = ft_strtrim(line, "\t");
		if (line[0] != '\0')
			break;
	}
	cnt = 0;
	while(line[cnt] == ' ')
		cnt++;
	side = choose_side(env, line + cnt);
	if (side == FLOOR || side == CEIL)
	if (env->swne_path[side][0] != '\0')
		my_exit(1, env);
	while (line[cnt] != '.')
		cnt++;
	env->swne_path[side] = ft_strdup(line + cnt);
	puts(env->swne_path[side]);
	return (side);
}

int get_path(t_env *env)
{
	int	fd;
	int	cnt;
	int	side;

	cnt = 0;
	fd = open(env->map_name, O_RDONLY, 0);
	env->swne_path = malloc(sizeof(char *) * 4);
	cnt = -1;
	if (fd == -1)
		my_exit(1, env);
	while (++cnt < 4)
		env->swne_path[cnt] = ft_calloc(1, 1);
	cnt = 0;
	while (cnt < 4)
	{
		side = get_pic_path(env, fd);
		cnt++;
	}
	cnt = -1;
	return (1);
}

//2 func