#include "ft_cub3d.h"

t_point ft_point(int x, int y)
{
	t_point	point;

	point.x = x;
	point.y = y;
	return (point);
}

void	ft_put_pixel(t_point point, int color)
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

int ft_put_line(int x, int y1, int y2, int color)
{
	int i;

	i = x;
	while (y1 != y2)
	{
		ft_put_pixel(ft_point(i, y1), color);
		if (y1 > y2)
			y1--;
		else
			y1++;
	}
	return (1);
}
