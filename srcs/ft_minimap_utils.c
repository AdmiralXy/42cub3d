#include "ft_cub3d.h"

t_minimap	*ft_compress_init(t_minimap *old_minimap)
{
	int			i;
	int			j;
	t_minimap	*minimap;

	minimap = malloc(sizeof(t_minimap));
	minimap->width = 0;
	minimap->height = 0;
	minimap->scale = old_minimap->scale;
	i = 0;
	while (i < old_minimap->height)
	{
		if (i % 2 == 0)
			(minimap->height)++;
		i++;
	}
	j = 0;
	while (j < old_minimap->width)
	{
		if (j % 2 == 0)
			(minimap->width)++;
		j++;
	}
	return (minimap);
}

t_minimap	*ft_minimap_compress(t_minimap *old_minimap)
{
	int			i;
	int			j;
	int			k;
	int			l;
	t_minimap	*minimap;

	i = 0;
	k = 0;
	minimap = ft_compress_init(old_minimap);
	minimap->map = malloc(sizeof(int *) * minimap->height);
	while (i < old_minimap->height)
	{
		if (i % 2 == 0)
		{
			minimap->map[k] = malloc(sizeof(int) * minimap->width);
			j = 0;
			l = 0;
			while (j < old_minimap->width)
			{
				if (j % 2 == 0)
				{
					minimap->map[k][l] = old_minimap->map[i][j];
					l++;
				}
				j++;
			}
			k++;
		}
		i++;
	}
	ft_clear_minimap(old_minimap);
	return (minimap);
}

t_minimap	*ft_stretch_columns(t_minimap *old_minimap)
{
	int			i;
	int			j;
	int 		k;
	t_minimap	*minimap;

	i = 0;
	k = 0;
	minimap = malloc(sizeof(t_minimap));
	minimap->width = old_minimap->width;
	minimap->height = old_minimap->height * 2;
	minimap->scale = old_minimap->scale;
	minimap->map = malloc(sizeof(int *) * minimap->height);
	while (i < old_minimap->height)
	{
		minimap->map[k] = malloc(sizeof(int) * minimap->width);
		minimap->map[k + 1] = malloc(sizeof(int) * minimap->width);
		j = -1;
		while (++j < old_minimap->width)
		{
			minimap->map[k][j] = old_minimap->map[i][j];
			minimap->map[k + 1][j] = old_minimap->map[i][j];
		}
		i++;
		k += 2;
	}
	ft_clear_minimap(old_minimap);
	return (minimap);
}

t_minimap	*ft_stretch_rows(t_minimap *old_minimap)
{
	int			i;
	int			j;
	int 		l;
	t_minimap	*minimap;

	i = 0;
	minimap = malloc(sizeof(t_minimap));
	minimap->width = old_minimap->width * 2;
	minimap->height = old_minimap->height;
	minimap->scale = old_minimap->scale;
	minimap->map = malloc(sizeof(int *) * minimap->height);
	while (i < old_minimap->height)
	{
		minimap->map[i] = malloc(sizeof(int) * minimap->width);
		j = -1;
		l = 0;
		while (++j < old_minimap->width)
		{
			minimap->map[i][l] = old_minimap->map[i][j];
			minimap->map[i][l + 1] = old_minimap->map[i][j];
			l += 2;
		}
		i++;
	}
	ft_clear_minimap(old_minimap);
	return (minimap);
}

t_minimap	*ft_minimap_stretch(t_minimap *old_minimap)
{
	t_minimap	*minimap;

	minimap = ft_stretch_columns(old_minimap);
	minimap = ft_stretch_rows(minimap);
	return (minimap);
}