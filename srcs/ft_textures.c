#include "ft_cub3d.h"

t_texture *ft_get_texture(t_env *env, char *path)
{
	t_texture *t;

	t = malloc(sizeof(t_texture));
	t->image = mlx_xpm_file_to_image(env->mlx, path, &(t->width), &(t->height));
	t->texture = (int *)mlx_get_data_addr(t->image, &(t->bpp), &(t->size_line), &(t->endian));
	return (t);
}
