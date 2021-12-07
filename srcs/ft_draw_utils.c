#include "ft_cub3d.h"

int	ft_rgb_to_hex(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

t_point	ft_point(int x, int y)
{
	t_point	point;

	point.x = x;
	point.y = y;
	return (point);
}

t_texture	*ft_get_texture(t_env *env, char *path)
{
	t_texture	*t;

	t = malloc(sizeof(t_texture));
	t->image = mlx_xpm_file_to_image(env->mlx, path, &(t->width), &(t->height));
	if (!t->image)
	{
		ft_error("texture is invalid!");
		exit(1);
	}
	t->texture = (int *)mlx_get_data_addr(t->image, &(t->bpp),
			&(t->size_line), &(t->endian));
	return (t);
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

void	ft_put_pixel_oft(t_env *env, t_point point, int color, int offset)
{
	int	pixel;

	point.x += offset;
	point.y += offset;
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
