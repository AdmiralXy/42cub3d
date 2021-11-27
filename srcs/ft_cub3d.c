#include "ft_cub3d.h"

void	ft_draw(void)
{
	mlx_put_image_to_window(env->mlx, env->mlx_win, env->img_ptr, 0, 0);
}

void drawBuffer(int buffer[1280][720])
{
	int i = 0, j;

	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			ft_put_pixel(ft_point(j, i), buffer[i][j]);
			j++;
		}
		i++;
	}
}

int **texture;

char *get_image(char *path, int width, int height)
{
	int *image;
	char *image_data;
	int image_info;

	image = mlx_xpm_file_to_image(env->mlx, path, &width, &height);
	image_data = mlx_get_data_addr(image, &image_info, &image_info, &image_info);
	//mlx_destroy_image(env->mlx, image);
	return (image_data);
}

void ft_drawing_test()
{
	ft_bzero(env->img_data, WIN_WIDTH * WIN_HEIGHT * (env->bpp / 8));

	for(int x = 0; x < WIN_HEIGHT; x++)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double) WIN_HEIGHT - 1; //x-coordinate in camera space
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;
		//which box of the map we're in
		int mapX = (int) posX;
		int mapY = (int) posY;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		//these are derived as:
		//deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX))
		//deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY))
		//which can be simplified to abs(|rayDir| / rayDirX) and abs(|rayDir| / rayDirY)
		//where |rayDir| is the length of the vector (rayDirX, rayDirY). Its length,
		//unlike (dirX, dirY) is not 1, however this does not matter, only the
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
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
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
		//This can be computed as (mapX - posX + (1 - stepX) / 2) / rayDirX for side == 0, or same formula with Y
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
		int texNum = env->world_map[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if(side == 0) wallX = posY + perpWallDist * rayDirY;
		else          wallX = posX + perpWallDist * rayDirX;
		wallX -= floor((wallX));

		//x coordinate on the texture
		int texX = (int)(wallX * (double)(texWidth));
		if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
		if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;

		// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * texHeight / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - pitch - WIN_HEIGHT / 2 + lineHeight / 2) * step;
		for(int y = drawStart; y < drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (texHeight - 1);
			texPos += step;
			int color = texture[texNum][texHeight * texY + texX];
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if(side == 1) color = (color >> 1) & 8355711;
			ft_put_pixel(ft_point(x, y), color);
		}
	}
}

int	main(void)
{
	if (!ft_initialize())
		return (1);
	if (!ft_parser())
		return (1);
	// x and y start position
	posX = 22;
	posY = 12;
	// initial direction vector
	dirX = -1;
	dirY = 0;
	// the 2d raycaster version of camera plane
	planeX = 0;
	planeY = 0.66;
	texture = malloc(sizeof(int *) * 8);
	texture[0] = (int *)get_image("pics/redbrick.xpm", 64, 64);
	texture[1] = (int *)get_image("pics/barrel.xpm", 64, 64);
	texture[2] = (int *)get_image("pics/colorstone.xpm", 64, 64);
	texture[3] = (int *)get_image("pics/eagle.xpm", 64, 64);
	texture[4] = (int *)get_image("pics/greystone.xpm", 64, 64);
	texture[5] = (int *)get_image("pics/purplestone.xpm", 64, 64);
	texture[6] = (int *)get_image("pics/wood.xpm", 64, 64);
	texture[7] = (int *)get_image("pics/greenlight.xpm", 64, 64);
	ft_drawing_test();
	ft_draw();
	mlx_loop(env->mlx);
	return (0);
}
