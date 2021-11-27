#include "ft_cub3d.h"

unsigned int	ft_rgb_to_hex(int r, int g, int b)
{
	return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

t_point ft_point(int x, int y)
{
	t_point	point;

	point.x = x;
	point.y = y;
	return (point);
}

void	ft_put_pixel(t_env *env, t_point point, int color)
{
	int	pixel;

	pixel = (point.y * WIN_HEIGHT * 4) + (point.x * 4);
	color = mlx_get_color_value(env->mlx, color);
	if (point.x > 0 && pixel > 0
		&& pixel < WIN_WIDTH * WIN_HEIGHT * (env->bpp / 8))
	{
		env->img_data[pixel + 0] = (char)((color) & 0xFF);
		env->img_data[pixel + 1] = (char)((color >> 8) & 0xFF);
		env->img_data[pixel + 2] = (char)((color >> 16) & 0xFF);
		env->img_data[pixel + 3] = (char)((color >> 24));
	}
}
