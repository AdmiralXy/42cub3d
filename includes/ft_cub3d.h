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
# define WIN_TITLE "42cub3d - made by kricky & faggar"
# define WIN_HEIGHT 1280
# define WIN_WIDTH 720
# define TX_WIDTH 64
# define TX_HEIGHT 64
# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

// Controls
# if __APPLE__
#  define KEY_EXIT 53
#  define KEY_UP 13
#  define KEY_DOWN 1
#  define KEY_LEFT 0
#  define KEY_RIGHT 2
# else
#  define KEY_EXIT 65307
#  define KEY_UP 119
#  define KEY_DOWN 115
#  define KEY_LEFT 97
#  define KEY_RIGHT 100

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
	int		direction;
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

typedef struct s_env
{
	void			*mlx;
	void			*mlx_win;
	int				bpp;
	int				size_line;
	int				endian;
	void			*img_ptr;
	char			*img_data;
	int				**world_map;
	int				world_width;
	int				world_height;
	unsigned int	floor_color;
	unsigned int	ceil_color;
	t_texture		**textures;
	t_player		p;
}	t_env;

// Initialization functions
int				ft_initialize(t_env *env);
int				ft_initialize_graphics(t_env *env);

// Parser functions
int				ft_parser(t_env *env);

// Drawing utilities functions
unsigned int	ft_rgb_to_hex(int r, int g, int b);
t_point			ft_point(int x, int y);
void			ft_put_pixel(t_env *env, t_point point, int color);

// Textures functions
t_texture		*ft_get_texture(t_env *env, char *path);

// Moving functions
int				ft_move_forward(t_env *env);
int				ft_move_back(t_env *env);
int				ft_camera_left(t_env *env, double angle);
int				ft_camera_right(t_env *env, double angle);

#endif
