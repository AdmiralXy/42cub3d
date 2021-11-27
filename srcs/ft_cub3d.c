#include "ft_cub3d.h"

void	ft_draw(t_env *env)
{
	mlx_put_image_to_window(env->mlx, env->mlx_win, env->img_ptr, 0, 0);
}

void ft_drawing_test(t_env *env)
{
	ft_bzero(env->img_data, WIN_WIDTH * WIN_HEIGHT * (env->bpp / 8));

	for(int x = 0; x < WIN_HEIGHT; x++)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double) WIN_HEIGHT - 1; //x-coordinate in camera space
		double rayDirX = env->p.dir_x + env->p.plane_x * cameraX;
		double rayDirY = env->p.dir_y + env->p.plane_y * cameraX;
		//which box of the map we're in
		int mapX = (int) env->p.pos_x;
		int mapY = (int) env->p.pos_y;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		//these are derived as:
		//deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX))
		//deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY))
		//which can be simplified to abs(|rayDir| / rayDirX) and abs(|rayDir| / rayDirY)
		//where |rayDir| is the length of the vector (rayDirX, rayDirY). Its length,
		//unlike (dir_x, dir_y) is not 1, however this does not matter, only the
		//ratio between deltaDistX and deltaDistY matters, due to the way the DDA
		//stepping further below works. So the values can be computed as below.
		// Division through zero is prevented, even though technically that's not
		// needed in C++ with IEEE 754 floating point values.
		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (env->p.pos_x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - env->p.pos_x) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (env->p.pos_y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - env->p.pos_y) * deltaDistY;
		}
		//perform DDA
		while(hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if(sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if(env->world_map[mapX][mapY] > 0) hit = 1;
		}
		//Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
		//hit to the camera plane. Euclidean to center camera point would give fisheye effect!
		//This can be computed as (mapX - pos_x + (1 - stepX) / 2) / rayDirX for side == 0, or same formula with Y
		//for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
		//because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
		//steps, but we subtract deltaDist once because one step more into the wall was taken above.

		//Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
		if(side == 0) perpWallDist = (sideDistX - deltaDistX);
		else          perpWallDist = (sideDistY - deltaDistY);

		//Calculate height of line to draw on screen
		int lineHeight = (int)(WIN_HEIGHT / perpWallDist);


		int pitch = 1;

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
		if(drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
		if(drawEnd >= WIN_HEIGHT) drawEnd = WIN_HEIGHT - 1;

		//texturing calculations
		//int texNum = env->world_map[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if(side == 0) wallX = env->p.pos_y + perpWallDist * rayDirY;
		else          wallX = env->p.pos_x + perpWallDist * rayDirX;
		wallX -= floor((wallX));

		//x coordinate on the texture
		int texX = (int)(wallX * (double)(TX_WIDTH));
		if(side == 0 && rayDirX > 0) texX = TX_WIDTH - texX - 1;
		if(side == 1 && rayDirY < 0) texX = TX_WIDTH - texX - 1;

		// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * TX_HEIGHT / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - pitch - WIN_HEIGHT / 2 + lineHeight / 2) * step;
		for(int y = drawStart; y < drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (TX_HEIGHT - 1) in case of overflow
			int texY = (int)texPos & (TX_HEIGHT - 1);
			texPos += step;
			int color;
			if (side == 0 && rayDirX > 0)
				color = env->textures[0]->texture[TX_HEIGHT * texY + texX];
			else if (side == 0 && rayDirX < 0)
				color = env->textures[1]->texture[TX_HEIGHT * texY + texX];
			else if (side == 1 && rayDirY > 0)
				color = env->textures[2]->texture[TX_HEIGHT * texY + texX];
			else if (side == 1 && rayDirY < 0)
				color = env->textures[3]->texture[TX_HEIGHT * texY + texX];
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if(side == 1) color = (color >> 1) & 8355711;
			ft_put_pixel(env, ft_point(x, y), color);
		}
	}
}

int	main(void)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!ft_initialize(env))
		return (1);
	if (!ft_parser(env))
		return (1);
	ft_initialize_graphics(env);
	ft_drawing_test(env);
	ft_draw(env);
	mlx_loop(env->mlx);
	return (0);
}
