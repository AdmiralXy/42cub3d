#include "ft_cub3d.h"

void	ft_clear_minimap(t_minimap *minimap)
{
	int	i;

	i = 0;
	while (i < minimap->height)
	{
		free(minimap->map[i]);
		i++;
	}
	free(minimap->map);
	free(minimap);
}

t_minimap	*ft_minimap_init(t_env *env)
{
	int			i;
	int			j;
	t_minimap	*minimap;

	i = 0;
	minimap = malloc(sizeof(t_minimap));
	minimap->scale = 0;
	minimap->map = malloc(sizeof(int *) * env->world_height);
	while (i < env->world_height)
	{
		j = 0;
		minimap->map[i] = malloc(sizeof(int) * env->world_width);
		while (j < env->world_width)
		{
			if (i == (int)env->p.pos_x && j == (int)env->p.pos_y)
				minimap->map[i][j] = 2;
			else
				minimap->map[i][j] = env->world_map[i][j];
			j++;
		}
		i++;
	}
	minimap->width = env->world_width;
	minimap->height = env->world_height;
	return (minimap);
}

void	ft_minimap_to_screen(t_env *env)
{
	int i;
	int	j;

	i = 0;
	while (i < env->minimap->height)
	{
		j = 0;
		while (j < env->minimap->width)
		{
			if (env->minimap->map[i][j] == 2)
				ft_put_pixel_oft(env, ft_point(i, j), MP_PLAYER, MP_OFFSET);
			else if (env->minimap->map[i][j] == 1)
				ft_put_pixel_oft(env, ft_point(i, j), MP_WALLS, MP_OFFSET);
			else
				ft_put_pixel_oft(env, ft_point(i, j), MP_SPACE, MP_OFFSET);
			j++;
		}
		i++;
	}
}

void	ft_minimap(t_env *env)
{
	env->minimap = ft_minimap_init(env);
	while (env->minimap->width < 100 || env->minimap->width > 500)
	{
		if (env->minimap->width < 100)
		{
			env->minimap = ft_minimap_stretch(env->minimap);
			env->minimap->scale += 4;
		}
		else if (env->minimap->width > 500)
		{
			env->minimap = ft_minimap_compress(env->minimap);
			env->minimap->scale -= 4;
		}
	}
	ft_minimap_to_screen(env);
	ft_clear_minimap(env->minimap);
}
