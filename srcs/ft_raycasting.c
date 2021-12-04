#include "ft_cub3d.h"

void	ft_fill_ceil_floor(t_env *env)
{
	int	x;
	int	y;

	y = WIN_HEIGHT / 2;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_HEIGHT * 2)
		{
			ft_put_pixel(env, ft_point(x, y), (int)env->floor_color);
			ft_put_pixel(env, ft_point(x, WIN_HEIGHT - y - 1),
				(int)env->ceil_color);
			x++;
		}
		y++;
	}
}

void	ft_set_tx_n(t_raycasting *rcs)
{
	if (rcs->side == 0 && rcs->ray_dir_x > 0)
		rcs->tx_n = NORTH;
	else if (rcs->side == 0 && rcs->ray_dir_x < 0)
		rcs->tx_n = SOUTH;
	else if (rcs->side == 1 && rcs->ray_dir_y > 0)
		rcs->tx_n = EAST;
	else if (rcs->side == 1 && rcs->ray_dir_y < 0)
		rcs->tx_n = WEST;
}

void	ft_raycasting_calculate(t_env *env, t_raycasting *rcs)
{
	if (rcs->side == 0)
		rcs->perp_wall_dist = (rcs->side_dist_x - rcs->delta_dist_x);
	else
		rcs->perp_wall_dist = (rcs->side_dist_y - rcs->delta_dist_y);
	rcs->line_height = (int)(WIN_HEIGHT / rcs->perp_wall_dist);
	rcs->pitch = 1;
	rcs->draw_start = -rcs->line_height / 2 + WIN_HEIGHT / 2;
	if (rcs->draw_start < 0)
		rcs->draw_start = 0;
	rcs->draw_end = rcs->line_height / 2 + WIN_HEIGHT / 2;
	if (rcs->draw_end >= WIN_HEIGHT)
		rcs->draw_end = WIN_HEIGHT - 1;
	if (rcs->side == 0)
		rcs->wall_x = env->p.pos_y + rcs->perp_wall_dist * rcs->ray_dir_y;
	else
		rcs->wall_x = env->p.pos_x + rcs->perp_wall_dist * rcs->ray_dir_x;
	rcs->wall_x -= floor((rcs->wall_x));
	ft_set_tx_n(rcs);
	rcs->tex_x = (int)(rcs->wall_x * (double)(env->textures[rcs->tx_n]->width));
	if (rcs->side == 0 && rcs->ray_dir_x > 0)
		rcs->tex_x = env->textures[rcs->tx_n]->width - rcs->tex_x - 1;
	if (rcs->side == 1 && rcs->ray_dir_y < 0)
		rcs->tex_x = env->textures[rcs->tx_n]->width - rcs->tex_x - 1;
}

void	ft_raycasting_texturing(t_env *env, t_raycasting *rcs, int x)
{
	int	color;
	int	y;

	y = rcs->draw_start;
	rcs->step = 1.0 * env->textures[rcs->tx_n]->height / rcs->line_height;
	rcs->tex_pos = (rcs->draw_start - rcs->pitch - WIN_HEIGHT / 2
			+ rcs->line_height / 2) * rcs->step;
	while (y < rcs->draw_end)
	{
		rcs->tex_y = (int)rcs->tex_pos & (env->textures[rcs->tx_n]->height - 1);
		rcs->tex_pos += rcs->step;
		color = env->textures[rcs->tx_n]->texture[env->textures[rcs->tx_n]->height * rcs->tex_y + rcs->tex_x];
		if (rcs->side == 1)
			color = (color >> 1) & 8355711;
		ft_put_pixel(env, ft_point(x, y), color);
		y++;
	}
}

void	ft_raycasting(t_env *env)
{
	t_raycasting	rcs;
	int				x;

	ft_bzero(env->img_data, WIN_WIDTH * WIN_HEIGHT * (env->bpp / 8));
	ft_fill_ceil_floor(env);
	x = 0;
	while (x < WIN_HEIGHT)
	{
		ft_init_rays(env, &rcs, x);
		ft_raycasting_calculate(env, &rcs);
		ft_raycasting_texturing(env, &rcs, x);
		x++;
	}
	ft_minimap(env);
	mlx_put_image_to_window(env->mlx, env->mlx_win, env->img_ptr, 0, 0);
}
