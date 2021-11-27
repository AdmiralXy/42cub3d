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
# define texWidth 64
# define texHeight 64
# define COLOR_RED 0xFF0000
# define COLOR_GREEN 0x00FF00
# define COLOR_BLUE 0x0000ff
# define COLOR_WHITE 0xFFFFFF
# define COLOR_YELLOW 0xFFFF00

// Constants controls
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

typedef struct s_env
{
	void	*mlx;
	void	*mlx_win;
	int		bpp;
	int		size_line;
	int		endian;
	void	*img_ptr;
	char	*img_data;
	int		**world_map;
}	t_env;

// Globals
t_env *env;
double posX, posY;
double dirX, dirY;
double planeX, planeY;

// Initialization functions
int		ft_initialize(void);

// Parser functions
int		ft_parser();

// Drawing utilities functions
t_point	ft_point(int x, int y);
void	ft_put_pixel(t_point point, int color);
int		ft_put_line(int x, int y1, int y2, int color);

#endif
