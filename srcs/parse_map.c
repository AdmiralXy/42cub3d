#include "ft_cub3d.h"

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
	env->world_map[number] = malloc(sizeof(int) * cnt);
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
		env->world_map[number] = malloc(sizeof(int) * cnt);
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

int	rewrite_map(t_env *env)
{
	env->world_height = get_height(env);
	env->world_map = (int **)malloc(sizeof(int *) * env->world_height);
	printf("%d	%d\n", env->strs, env->world_height);
	get_cur_str(env);
	write_array_par(env);
	return 1;
}