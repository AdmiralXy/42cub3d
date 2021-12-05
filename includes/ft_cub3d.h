#ifndef FT_CUB3D_H
# define FT_CUB3D_H

// Libs
# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>

// Constants
# define WIN_TITLE "42cub3d"
# define WIN_HEIGHT 1280
# define WIN_WIDTH 720
# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3
# define FLOOR 111
# define CEIL 112
# define MP_WALLS 0x000000
# define MP_SPACE 0xffffff
# define MP_PLAYER 0x00ff48
# define MP_OFFSET 45

//map symbs
# define SPACE 5
# define SYMB_ONE 6
# define PLAYER_POS 10
# define SYMB_ZERO 7
# define PLAYER_NORTH 11
# define PLAYER_SOUTH 12
# define PLAYER_EAST 13
# define PLAYER_WEST 14

// Controls
# if __APPLE__
#  define KEY_EXIT 53
#  define KEY_UP 13
#  define KEY_DOWN 1
#  define KEY_LEFT 0
#  define KEY_RIGHT 2
#  define ARROW_LEFT 123
#  define ARROW_RIGHT 124
# else
#  define KEY_EXIT 65307
#  define KEY_UP 119
#  define KEY_DOWN 115
#  define KEY_LEFT 97
#  define KEY_RIGHT 100
#  define ARROW_LEFT 65361
#  define ARROW_RIGHT 65363

# endif

// Structures
typedef struct s_point
{
	int		x;
	int		y;
}	t_point;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rotation_speed;
	int		initial_direction;
}	t_player;

typedef struct s_texture
{
	int	*texture;
	int	*image;
	int	bpp;
	int	size_line;
	int	endian;
	int	width;
	int	height;
}	t_texture;

typedef struct s_minimap
{
	int	**map;
	int	height;
	int	width;
	int scale;
}	t_minimap;

typedef struct s_raycasting
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	int		tx_n;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		pitch;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
}	t_raycasting;

typedef struct s_env
{
	void		*mlx;
	void		*mlx_win;
	int			bpp;
	int			size_line;
	int			endian;
	void		*img_ptr;
	char		*img_data;
	int			**world_map;
	int			world_width;
	int			world_height;
	int			floor_color;
	int			ceil_color;

	char		*map_name;
	char		**swne_path;
	int			fd;
	int			strs;
	int			player;
	int			tmp;

	t_texture	**textures;
	t_player	p;
	t_minimap	*minimap;
}	t_env;

// Initialization functions
int			ft_initialize(t_env *env);
int			ft_initialize_graphics(t_env *env);

// Parser functions
int			ft_parser(t_env *env);

// Drawing utilities functions
int			ft_rgb_to_hex(int r, int g, int b);
t_texture	*ft_get_texture(t_env *env, char *path);
t_point		ft_point(int x, int y);
void		ft_put_pixel(t_env *env, t_point point, int color);
void		ft_put_pixel_oft(t_env *env, t_point point, int color, int offset);

// Raycasting functions
void		ft_raycasting(t_env *env);
void		ft_init_rays(t_env *env, t_raycasting *rcs, int x);

// Minimap functions
void		ft_minimap(t_env *env);
void		ft_clear_minimap(t_minimap *minimap);
t_minimap	*ft_minimap_compress(t_minimap *old_minimap);
t_minimap	*ft_minimap_stretch(t_minimap *old_minimap);

// Exit functions
int			ft_exit(t_env *env);

// Moving functions
int			ft_move_forward(t_env *env);
int			ft_move_back(t_env *env);
int			ft_move_left(t_env *env);
int			ft_move_right(t_env *env);
int			ft_camera_left(t_env *env, double angle);
int			ft_camera_right(t_env *env, double angle);
//Dinar
int	my_exit(int er_numb, t_env *env);
int get_path(t_env *env);
int	fill_floor_ceil(t_env *env, char *line, int f_or_c);
int	rewrite_map(t_env *env);
int	check_line(char *line);
int	get_height(t_env *env);
int get_cur_str(t_env *env);
int	validate_symb(char c);
int	finish_map_parser(t_env *env);
void	better_check_horizontal(t_env *env, int number, int cnt);
void	better_check_vertical(t_env *env, int number, int cnt);
void	check_first_last_str(t_env *env, int number);
void	fill_int_array(t_env *env, char *line, int number);
#endif
