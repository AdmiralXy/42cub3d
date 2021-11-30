#include "ft_cub3d.h"

/*
 * Парсер заполняет:
 * env->p.posX, env->p.posY - начальная позиция игрока по x и y на карте
 * env->p.initial_direction - начальное направление взгляда
 * 4 Текстуры - NORTH, SOUTH, EAST, WEST
 * env->floor_color, env->ceil_color - цвет потолка и пола
 * env->world_height, env->world_width - длина и ширина мира
 * env->world_map - двумерный массив int'ов, сам мир
 * Примечение: в двумерном массиве мира, N,S,E,W (игрок) заменяется цифрой 0
 * Функция возвращает int(1) если все прошло успешно, int(0) в противном случае
*/

int	check_char(char c)
{
	if (c != '0' && c != '1' && c != 'N' 
	&& c != 'W' && c != 'S' && c != 'E' && c != ' ')
		return(-1);
	return(1);
}

int	get_width(char *one_line)
{
	int	cnt;

	cnt = 0;
	while (one_line[cnt] != '\0')
	{
		if (check_char(one_line[cnt] == -1))
		{
			printf("Bad map\n");
			exit(1);
		}
		cnt++;
	}
	return (cnt);
}

int	*fill_data(int *int_str, char *line)
{
	int		cnt;

	cnt = 0;
	while (line[cnt] != '\0')
	{
		if (line[cnt] == ' ')
			int_str[cnt] = 0;
		else if (line[cnt] == '1')
			int_str[cnt] = 1;
		else if (line[cnt] == '0')
			int_str[cnt] = 0;
		cnt++;
	}
	return (int_str);
}

int	textures(char *line, t_env *env)
{
	int cnt;

	cnt = 0;
	if (ft_strncmp("NO", line, 2) == 0)
	{
		while (line[cnt] != '.')
		{
			env->textures[NORTH] = line + cnt;
		}
	}
	else if (ft_strncmp("SO", line, 2) == 0)
	{
		while (line[cnt] != '.')
		{
			env->textures[SOUTH] = line + cnt;
		}
	}
	else if (ft_strncmp("WE", line, 2) == 0)
	{
		while (line[cnt] != '.')
		{
			env->textures[WEST] = line + cnt;
		}
	}
	else if (ft_strncmp("EA", line, 2) == 0)
	{
		while (line[cnt] != '.')
		{
			env->textures[EAST] = line + cnt;
		}
	}
}

int	ft_get_floor_ceiling(char *line, int flag, t_env *env)
{
	int		cnt;
	char	**splt;

	cnt = 0;
	while (line[cnt] <= '0' && line[cnt] >= '9')
		cnt++;
	splt = ft_split(line + cnt, ',');
	if (split[0] == NULL || splt[2] == NULL 
		|| split[1] == NULL)
	{
		printf("Error\n");
		exit (-1);
	}
	else
	{
		if (flag == 0)
			env->floor_color = ft_rgb_to_hex(ft_atoi(splt[0],
			ft_atoi(splt[1], ft_atoi(splt[2]))));
		if (flag == 1)
			env->ceil_color = ft_rgb_to_hex(ft_atoi(splt[0],
			ft_atoi(splt[1], ft_atoi(splt[2]))))
	}
}

int	fill_textures(int fd, t_env *env)
{
	int		i;
	char	*line;

	i = 0;
	while (i < 8)
	{
		get_next_line(fd, &line);
		if(i < 4)
		{
			textures(line, env);
		}
		else if (i == 4)
		{
			get_next_line(fd, &line);
			ft_get_floor_ceiling(line, 0, env);
			get_next_line(fd, &line);
			ft_get_floor_ceiling(line, 0, env);
			// get_next_line(fd, &line);
			break;
		}

	}
}
void	skip_str(int fd, char *line)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		get_next_line(fd, line);
		i++;
	}
}
int	open_map(t_env *env, char **av)
{
	int 	fd;
	int		size;
	char	*line;
	int		height;

	height = 0;
	fd = open(av[1], O_RDONLY, 0);
	if (fd == -1)
		exit (1);
	size = 0;
	fill_textures(fd, env);
	while (get_next_line(fd, &line) && height < 8)
	{
		height++;
	}
	close(fd);
	env->world_map = malloc(sizeof(int *) * height);
	fd = open(av[1], O_RDONLY, 0);
	skip_str(fd, line);
	while (get_next_line(fd, &line))
	{
		env->world_map[size] = malloc(sizeof(int) * get_width(line));
		env->world_map[size] = fill_data(env->world_map[size], line);
	}
	return (1);
}

int	ft_parser(t_env *env)
{
	int	i;

	env->p.pos_x = 22;
	env->p.pos_y = 12;
	env->p.initial_direction = SOUTH;
	env->textures[NORTH] = ft_get_texture(env, "pics/redbrick.xpm");
	env->textures[SOUTH] = ft_get_texture(env, "pics/wood.xpm");
	env->textures[EAST] = ft_get_texture(env, "pics/bluestone.xpm");
	env->textures[WEST] = ft_get_texture(env, "pics/mossy.xpm");
	env->floor_color = ft_rgb_to_hex(96, 99, 99);
	env->ceil_color = ft_rgb_to_hex(183, 241, 247);
	env->world_width = 24;
	env->world_height = 24;
	env->world_map = malloc(sizeof(int *) * env->world_height);
	i = 0;
	while (i < 24)
	{
		env->world_map[i] = malloc(sizeof(int) * env->world_width);
		i++;
	}
	env->world_map[0][0] = 1;
	env->world_map[0][1] = 1;
	env->world_map[0][2] = 1;
	env->world_map[0][3] = 1;
	env->world_map[0][4] = 1;
	env->world_map[0][5] = 1;
	env->world_map[0][6] = 1;
	env->world_map[0][7] = 1;
	env->world_map[0][8] = 1;
	env->world_map[0][9] = 1;
	env->world_map[0][10] = 1;
	env->world_map[0][11] = 1;
	env->world_map[0][12] = 1;
	env->world_map[0][13] = 1;
	env->world_map[0][14] = 1;
	env->world_map[0][15] = 1;
	env->world_map[0][16] = 1;
	env->world_map[0][17] = 1;
	env->world_map[0][18] = 1;
	env->world_map[0][19] = 1;
	env->world_map[0][20] = 1;
	env->world_map[0][21] = 1;
	env->world_map[0][22] = 1;
	env->world_map[0][23] = 1;
	env->world_map[1][0] = 1;
	env->world_map[1][1] = 0;
	env->world_map[1][2] = 0;
	env->world_map[1][3] = 0;
	env->world_map[1][4] = 0;
	env->world_map[1][5] = 0;
	env->world_map[1][6] = 0;
	env->world_map[1][7] = 0;
	env->world_map[1][8] = 0;
	env->world_map[1][9] = 0;
	env->world_map[1][10] = 0;
	env->world_map[1][11] = 0;
	env->world_map[1][12] = 0;
	env->world_map[1][13] = 0;
	env->world_map[1][14] = 0;
	env->world_map[1][15] = 0;
	env->world_map[1][16] = 0;
	env->world_map[1][17] = 0;
	env->world_map[1][18] = 0;
	env->world_map[1][19] = 0;
	env->world_map[1][20] = 0;
	env->world_map[1][21] = 0;
	env->world_map[1][22] = 0;
	env->world_map[1][23] = 1;
	env->world_map[2][0] = 1;
	env->world_map[2][1] = 0;
	env->world_map[2][2] = 0;
	env->world_map[2][3] = 0;
	env->world_map[2][4] = 0;
	env->world_map[2][5] = 0;
	env->world_map[2][6] = 0;
	env->world_map[2][7] = 0;
	env->world_map[2][8] = 0;
	env->world_map[2][9] = 0;
	env->world_map[2][10] = 0;
	env->world_map[2][11] = 0;
	env->world_map[2][12] = 0;
	env->world_map[2][13] = 0;
	env->world_map[2][14] = 0;
	env->world_map[2][15] = 0;
	env->world_map[2][16] = 0;
	env->world_map[2][17] = 0;
	env->world_map[2][18] = 0;
	env->world_map[2][19] = 0;
	env->world_map[2][20] = 0;
	env->world_map[2][21] = 0;
	env->world_map[2][22] = 0;
	env->world_map[2][23] = 1;
	env->world_map[3][0] = 1;
	env->world_map[3][1] = 0;
	env->world_map[3][2] = 0;
	env->world_map[3][3] = 0;
	env->world_map[3][4] = 0;
	env->world_map[3][5] = 0;
	env->world_map[3][6] = 0;
	env->world_map[3][7] = 0;
	env->world_map[3][8] = 0;
	env->world_map[3][9] = 0;
	env->world_map[3][10] = 0;
	env->world_map[3][11] = 0;
	env->world_map[3][12] = 0;
	env->world_map[3][13] = 0;
	env->world_map[3][14] = 0;
	env->world_map[3][15] = 0;
	env->world_map[3][16] = 0;
	env->world_map[3][17] = 0;
	env->world_map[3][18] = 0;
	env->world_map[3][19] = 0;
	env->world_map[3][20] = 0;
	env->world_map[3][21] = 0;
	env->world_map[3][22] = 0;
	env->world_map[3][23] = 1;
	env->world_map[4][0] = 1;
	env->world_map[4][1] = 0;
	env->world_map[4][2] = 0;
	env->world_map[4][3] = 0;
	env->world_map[4][4] = 0;
	env->world_map[4][5] = 0;
	env->world_map[4][6] = 1;
	env->world_map[4][7] = 1;
	env->world_map[4][8] = 1;
	env->world_map[4][9] = 1;
	env->world_map[4][10] = 1;
	env->world_map[4][11] = 0;
	env->world_map[4][12] = 0;
	env->world_map[4][13] = 0;
	env->world_map[4][14] = 0;
	env->world_map[4][15] = 1;
	env->world_map[4][16] = 0;
	env->world_map[4][17] = 1;
	env->world_map[4][18] = 0;
	env->world_map[4][19] = 1;
	env->world_map[4][20] = 0;
	env->world_map[4][21] = 0;
	env->world_map[4][22] = 0;
	env->world_map[4][23] = 1;
	env->world_map[5][0] = 1;
	env->world_map[5][1] = 0;
	env->world_map[5][2] = 0;
	env->world_map[5][3] = 0;
	env->world_map[5][4] = 0;
	env->world_map[5][5] = 0;
	env->world_map[5][6] = 1;
	env->world_map[5][7] = 0;
	env->world_map[5][8] = 0;
	env->world_map[5][9] = 0;
	env->world_map[5][10] = 1;
	env->world_map[5][11] = 0;
	env->world_map[5][12] = 0;
	env->world_map[5][13] = 0;
	env->world_map[5][14] = 0;
	env->world_map[5][15] = 0;
	env->world_map[5][16] = 0;
	env->world_map[5][17] = 0;
	env->world_map[5][18] = 0;
	env->world_map[5][19] = 0;
	env->world_map[5][20] = 0;
	env->world_map[5][21] = 0;
	env->world_map[5][22] = 0;
	env->world_map[5][23] = 1;
	env->world_map[6][0] = 1;
	env->world_map[6][1] = 0;
	env->world_map[6][2] = 0;
	env->world_map[6][3] = 0;
	env->world_map[6][4] = 0;
	env->world_map[6][5] = 0;
	env->world_map[6][6] = 1;
	env->world_map[6][7] = 0;
	env->world_map[6][8] = 0;
	env->world_map[6][9] = 0;
	env->world_map[6][10] = 1;
	env->world_map[6][11] = 0;
	env->world_map[6][12] = 0;
	env->world_map[6][13] = 0;
	env->world_map[6][14] = 0;
	env->world_map[6][15] = 1;
	env->world_map[6][16] = 0;
	env->world_map[6][17] = 0;
	env->world_map[6][18] = 0;
	env->world_map[6][19] = 1;
	env->world_map[6][20] = 0;
	env->world_map[6][21] = 0;
	env->world_map[6][22] = 0;
	env->world_map[6][23] = 1;
	env->world_map[7][0] = 1;
	env->world_map[7][1] = 0;
	env->world_map[7][2] = 0;
	env->world_map[7][3] = 0;
	env->world_map[7][4] = 0;
	env->world_map[7][5] = 0;
	env->world_map[7][6] = 1;
	env->world_map[7][7] = 0;
	env->world_map[7][8] = 0;
	env->world_map[7][9] = 0;
	env->world_map[7][10] = 1;
	env->world_map[7][11] = 0;
	env->world_map[7][12] = 0;
	env->world_map[7][13] = 0;
	env->world_map[7][14] = 0;
	env->world_map[7][15] = 0;
	env->world_map[7][16] = 0;
	env->world_map[7][17] = 0;
	env->world_map[7][18] = 0;
	env->world_map[7][19] = 0;
	env->world_map[7][20] = 0;
	env->world_map[7][21] = 0;
	env->world_map[7][22] = 0;
	env->world_map[7][23] = 1;
	env->world_map[8][0] = 1;
	env->world_map[8][1] = 0;
	env->world_map[8][2] = 0;
	env->world_map[8][3] = 0;
	env->world_map[8][4] = 0;
	env->world_map[8][5] = 0;
	env->world_map[8][6] = 1;
	env->world_map[8][7] = 1;
	env->world_map[8][8] = 0;
	env->world_map[8][9] = 1;
	env->world_map[8][10] = 1;
	env->world_map[8][11] = 0;
	env->world_map[8][12] = 0;
	env->world_map[8][13] = 0;
	env->world_map[8][14] = 0;
	env->world_map[8][15] = 1;
	env->world_map[8][16] = 0;
	env->world_map[8][17] = 1;
	env->world_map[8][18] = 0;
	env->world_map[8][19] = 1;
	env->world_map[8][20] = 0;
	env->world_map[8][21] = 0;
	env->world_map[8][22] = 0;
	env->world_map[8][23] = 1;
	env->world_map[9][0] = 1;
	env->world_map[9][1] = 0;
	env->world_map[9][2] = 0;
	env->world_map[9][3] = 0;
	env->world_map[9][4] = 0;
	env->world_map[9][5] = 0;
	env->world_map[9][6] = 0;
	env->world_map[9][7] = 0;
	env->world_map[9][8] = 0;
	env->world_map[9][9] = 0;
	env->world_map[9][10] = 0;
	env->world_map[9][11] = 0;
	env->world_map[9][12] = 0;
	env->world_map[9][13] = 0;
	env->world_map[9][14] = 0;
	env->world_map[9][15] = 0;
	env->world_map[9][16] = 0;
	env->world_map[9][17] = 0;
	env->world_map[9][18] = 0;
	env->world_map[9][19] = 0;
	env->world_map[9][20] = 0;
	env->world_map[9][21] = 0;
	env->world_map[9][22] = 0;
	env->world_map[9][23] = 1;
	env->world_map[10][0] = 1;
	env->world_map[10][1] = 0;
	env->world_map[10][2] = 0;
	env->world_map[10][3] = 0;
	env->world_map[10][4] = 0;
	env->world_map[10][5] = 0;
	env->world_map[10][6] = 0;
	env->world_map[10][7] = 0;
	env->world_map[10][8] = 0;
	env->world_map[10][9] = 0;
	env->world_map[10][10] = 0;
	env->world_map[10][11] = 0;
	env->world_map[10][12] = 0;
	env->world_map[10][13] = 0;
	env->world_map[10][14] = 0;
	env->world_map[10][15] = 0;
	env->world_map[10][16] = 0;
	env->world_map[10][17] = 0;
	env->world_map[10][18] = 0;
	env->world_map[10][19] = 0;
	env->world_map[10][20] = 0;
	env->world_map[10][21] = 0;
	env->world_map[10][22] = 0;
	env->world_map[10][23] = 1;
	env->world_map[11][0] = 1;
	env->world_map[11][1] = 0;
	env->world_map[11][2] = 0;
	env->world_map[11][3] = 0;
	env->world_map[11][4] = 0;
	env->world_map[11][5] = 0;
	env->world_map[11][6] = 0;
	env->world_map[11][7] = 0;
	env->world_map[11][8] = 0;
	env->world_map[11][9] = 0;
	env->world_map[11][10] = 0;
	env->world_map[11][11] = 0;
	env->world_map[11][12] = 0;
	env->world_map[11][13] = 0;
	env->world_map[11][14] = 0;
	env->world_map[11][15] = 0;
	env->world_map[11][16] = 0;
	env->world_map[11][17] = 0;
	env->world_map[11][18] = 0;
	env->world_map[11][19] = 0;
	env->world_map[11][20] = 0;
	env->world_map[11][21] = 0;
	env->world_map[11][22] = 0;
	env->world_map[11][23] = 1;
	env->world_map[12][0] = 1;
	env->world_map[12][1] = 0;
	env->world_map[12][2] = 0;
	env->world_map[12][3] = 0;
	env->world_map[12][4] = 0;
	env->world_map[12][5] = 0;
	env->world_map[12][6] = 0;
	env->world_map[12][7] = 0;
	env->world_map[12][8] = 0;
	env->world_map[12][9] = 0;
	env->world_map[12][10] = 0;
	env->world_map[12][11] = 0;
	env->world_map[12][12] = 0;
	env->world_map[12][13] = 0;
	env->world_map[12][14] = 0;
	env->world_map[12][15] = 0;
	env->world_map[12][16] = 0;
	env->world_map[12][17] = 0;
	env->world_map[12][18] = 0;
	env->world_map[12][19] = 0;
	env->world_map[12][20] = 0;
	env->world_map[12][21] = 0;
	env->world_map[12][22] = 0;
	env->world_map[12][23] = 1;
	env->world_map[13][0] = 1;
	env->world_map[13][1] = 0;
	env->world_map[13][2] = 0;
	env->world_map[13][3] = 0;
	env->world_map[13][4] = 0;
	env->world_map[13][5] = 0;
	env->world_map[13][6] = 0;
	env->world_map[13][7] = 0;
	env->world_map[13][8] = 0;
	env->world_map[13][9] = 0;
	env->world_map[13][10] = 0;
	env->world_map[13][11] = 0;
	env->world_map[13][12] = 0;
	env->world_map[13][13] = 0;
	env->world_map[13][14] = 0;
	env->world_map[13][15] = 0;
	env->world_map[13][16] = 0;
	env->world_map[13][17] = 0;
	env->world_map[13][18] = 0;
	env->world_map[13][19] = 0;
	env->world_map[13][20] = 0;
	env->world_map[13][21] = 0;
	env->world_map[13][22] = 0;
	env->world_map[13][23] = 1;
	env->world_map[14][0] = 1;
	env->world_map[14][1] = 0;
	env->world_map[14][2] = 0;
	env->world_map[14][3] = 0;
	env->world_map[14][4] = 0;
	env->world_map[14][5] = 0;
	env->world_map[14][6] = 0;
	env->world_map[14][7] = 0;
	env->world_map[14][8] = 0;
	env->world_map[14][9] = 0;
	env->world_map[14][10] = 0;
	env->world_map[14][11] = 0;
	env->world_map[14][12] = 0;
	env->world_map[14][13] = 0;
	env->world_map[14][14] = 0;
	env->world_map[14][15] = 0;
	env->world_map[14][16] = 0;
	env->world_map[14][17] = 0;
	env->world_map[14][18] = 0;
	env->world_map[14][19] = 0;
	env->world_map[14][20] = 0;
	env->world_map[14][21] = 0;
	env->world_map[14][22] = 0;
	env->world_map[14][23] = 1;
	env->world_map[15][0] = 1;
	env->world_map[15][1] = 0;
	env->world_map[15][2] = 0;
	env->world_map[15][3] = 0;
	env->world_map[15][4] = 0;
	env->world_map[15][5] = 0;
	env->world_map[15][6] = 0;
	env->world_map[15][7] = 0;
	env->world_map[15][8] = 0;
	env->world_map[15][9] = 0;
	env->world_map[15][10] = 0;
	env->world_map[15][11] = 0;
	env->world_map[15][12] = 0;
	env->world_map[15][13] = 0;
	env->world_map[15][14] = 0;
	env->world_map[15][15] = 0;
	env->world_map[15][16] = 0;
	env->world_map[15][17] = 0;
	env->world_map[15][18] = 0;
	env->world_map[15][19] = 0;
	env->world_map[15][20] = 0;
	env->world_map[15][21] = 0;
	env->world_map[15][22] = 0;
	env->world_map[15][23] = 1;
	env->world_map[16][0] = 1;
	env->world_map[16][1] = 1;
	env->world_map[16][2] = 1;
	env->world_map[16][3] = 1;
	env->world_map[16][4] = 1;
	env->world_map[16][5] = 1;
	env->world_map[16][6] = 1;
	env->world_map[16][7] = 1;
	env->world_map[16][8] = 1;
	env->world_map[16][9] = 0;
	env->world_map[16][10] = 0;
	env->world_map[16][11] = 0;
	env->world_map[16][12] = 0;
	env->world_map[16][13] = 0;
	env->world_map[16][14] = 0;
	env->world_map[16][15] = 0;
	env->world_map[16][16] = 0;
	env->world_map[16][17] = 0;
	env->world_map[16][18] = 0;
	env->world_map[16][19] = 0;
	env->world_map[16][20] = 0;
	env->world_map[16][21] = 0;
	env->world_map[16][22] = 0;
	env->world_map[16][23] = 1;
	env->world_map[17][0] = 1;
	env->world_map[17][1] = 1;
	env->world_map[17][2] = 0;
	env->world_map[17][3] = 1;
	env->world_map[17][4] = 0;
	env->world_map[17][5] = 0;
	env->world_map[17][6] = 0;
	env->world_map[17][7] = 0;
	env->world_map[17][8] = 1;
	env->world_map[17][9] = 0;
	env->world_map[17][10] = 0;
	env->world_map[17][11] = 0;
	env->world_map[17][12] = 0;
	env->world_map[17][13] = 0;
	env->world_map[17][14] = 0;
	env->world_map[17][15] = 0;
	env->world_map[17][16] = 0;
	env->world_map[17][17] = 0;
	env->world_map[17][18] = 0;
	env->world_map[17][19] = 0;
	env->world_map[17][20] = 0;
	env->world_map[17][21] = 0;
	env->world_map[17][22] = 0;
	env->world_map[17][23] = 1;
	env->world_map[18][0] = 1;
	env->world_map[18][1] = 1;
	env->world_map[18][2] = 0;
	env->world_map[18][3] = 0;
	env->world_map[18][4] = 0;
	env->world_map[18][5] = 0;
	env->world_map[18][6] = 1;
	env->world_map[18][7] = 0;
	env->world_map[18][8] = 1;
	env->world_map[18][9] = 0;
	env->world_map[18][10] = 0;
	env->world_map[18][11] = 0;
	env->world_map[18][12] = 0;
	env->world_map[18][13] = 0;
	env->world_map[18][14] = 0;
	env->world_map[18][15] = 0;
	env->world_map[18][16] = 0;
	env->world_map[18][17] = 0;
	env->world_map[18][18] = 0;
	env->world_map[18][19] = 0;
	env->world_map[18][20] = 0;
	env->world_map[18][21] = 0;
	env->world_map[18][22] = 0;
	env->world_map[18][23] = 1;
	env->world_map[19][0] = 1;
	env->world_map[19][1] = 1;
	env->world_map[19][2] = 0;
	env->world_map[19][3] = 1;
	env->world_map[19][4] = 0;
	env->world_map[19][5] = 0;
	env->world_map[19][6] = 0;
	env->world_map[19][7] = 0;
	env->world_map[19][8] = 1;
	env->world_map[19][9] = 0;
	env->world_map[19][10] = 0;
	env->world_map[19][11] = 0;
	env->world_map[19][12] = 0;
	env->world_map[19][13] = 0;
	env->world_map[19][14] = 0;
	env->world_map[19][15] = 0;
	env->world_map[19][16] = 0;
	env->world_map[19][17] = 0;
	env->world_map[19][18] = 0;
	env->world_map[19][19] = 0;
	env->world_map[19][20] = 0;
	env->world_map[19][21] = 0;
	env->world_map[19][22] = 0;
	env->world_map[19][23] = 1;
	env->world_map[20][0] = 1;
	env->world_map[20][1] = 1;
	env->world_map[20][2] = 0;
	env->world_map[20][3] = 1;
	env->world_map[20][4] = 1;
	env->world_map[20][5] = 1;
	env->world_map[20][6] = 1;
	env->world_map[20][7] = 1;
	env->world_map[20][8] = 1;
	env->world_map[20][9] = 0;
	env->world_map[20][10] = 0;
	env->world_map[20][11] = 0;
	env->world_map[20][12] = 0;
	env->world_map[20][13] = 0;
	env->world_map[20][14] = 0;
	env->world_map[20][15] = 0;
	env->world_map[20][16] = 0;
	env->world_map[20][17] = 0;
	env->world_map[20][18] = 0;
	env->world_map[20][19] = 0;
	env->world_map[20][20] = 0;
	env->world_map[20][21] = 0;
	env->world_map[20][22] = 0;
	env->world_map[20][23] = 1;
	env->world_map[21][0] = 1;
	env->world_map[21][1] = 1;
	env->world_map[21][2] = 0;
	env->world_map[21][3] = 0;
	env->world_map[21][4] = 0;
	env->world_map[21][5] = 0;
	env->world_map[21][6] = 0;
	env->world_map[21][7] = 0;
	env->world_map[21][8] = 0;
	env->world_map[21][9] = 0;
	env->world_map[21][10] = 0;
	env->world_map[21][11] = 0;
	env->world_map[21][12] = 0;
	env->world_map[21][13] = 0;
	env->world_map[21][14] = 0;
	env->world_map[21][15] = 0;
	env->world_map[21][16] = 0;
	env->world_map[21][17] = 0;
	env->world_map[21][18] = 0;
	env->world_map[21][19] = 0;
	env->world_map[21][20] = 0;
	env->world_map[21][21] = 0;
	env->world_map[21][22] = 0;
	env->world_map[21][23] = 1;
	env->world_map[22][0] = 1;
	env->world_map[22][1] = 1;
	env->world_map[22][2] = 1;
	env->world_map[22][3] = 1;
	env->world_map[22][4] = 1;
	env->world_map[22][5] = 1;
	env->world_map[22][6] = 1;
	env->world_map[22][7] = 1;
	env->world_map[22][8] = 1;
	env->world_map[22][9] = 0;
	env->world_map[22][10] = 0;
	env->world_map[22][11] = 0;
	env->world_map[22][12] = 0;
	env->world_map[22][13] = 0;
	env->world_map[22][14] = 0;
	env->world_map[22][15] = 0;
	env->world_map[22][16] = 0;
	env->world_map[22][17] = 0;
	env->world_map[22][18] = 0;
	env->world_map[22][19] = 0;
	env->world_map[22][20] = 0;
	env->world_map[22][21] = 0;
	env->world_map[22][22] = 0;
	env->world_map[22][23] = 1;
	env->world_map[23][0] = 1;
	env->world_map[23][1] = 1;
	env->world_map[23][2] = 1;
	env->world_map[23][3] = 1;
	env->world_map[23][4] = 1;
	env->world_map[23][5] = 1;
	env->world_map[23][6] = 1;
	env->world_map[23][7] = 1;
	env->world_map[23][8] = 1;
	env->world_map[23][9] = 1;
	env->world_map[23][10] = 1;
	env->world_map[23][11] = 1;
	env->world_map[23][12] = 1;
	env->world_map[23][13] = 1;
	env->world_map[23][14] = 1;
	env->world_map[23][15] = 1;
	env->world_map[23][16] = 1;
	env->world_map[23][17] = 1;
	env->world_map[23][18] = 1;
	env->world_map[23][19] = 1;
	env->world_map[23][20] = 1;
	env->world_map[23][21] = 1;
	env->world_map[23][22] = 1;
	env->world_map[23][23] = 1;
	return (1);
}
