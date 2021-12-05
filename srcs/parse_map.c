#include "ft_cub3d.h"

void	fill_int_p2(t_env *env, int number, int cnt)
{
	while (cnt < env->world_width)
	{
		env->world_map[number][cnt] = -1;
		cnt++;
	}
}


void	fill_int_array(t_env *env, char *line, int number)
{
	int	cnt;
	int	tmp;

	cnt = 0;
	while (line[cnt] != 0)
	{
		tmp = validate_symb(line[cnt]);
		if (tmp == SPACE)
			env->world_map[number][cnt] = -1;
		else if (tmp == SYMB_ONE)
			env->world_map[number][cnt] = 1;
		else if (tmp == SYMB_ZERO)
			env->world_map[number][cnt] = 0;
		else if (tmp >= PLAYER_NORTH && tmp <= PLAYER_WEST)
		{
			if (env->player != 0)
				my_exit(3, env);
			env->world_map[number][cnt] = tmp;
			env->player = 1;
		}
		cnt++;
	}
	fill_int_p2(env, number, cnt);
}

void	check_first_end(t_env *env, char *line, int number)
{
	int		cnt;
	char	a;

	cnt = 0;
	while(line[cnt] != 0)
	{
		a = line[cnt];
		if (a != '1' && a != ' ')
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
		while(line[cnt] != 0)
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
	while (cnt < env->world_height)
	{
		get_next_line(env->fd, &line);
		check_middle(env, line, cnt);
		cnt++;
	}
	return 1;
}

void malloc_arrays(t_env *env)
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
	return 1;
}