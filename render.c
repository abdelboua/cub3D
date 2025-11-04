#include "./header.h"

static void	put_pixel(t_datagame *data, int x, int y, int color)
{
	char	*pixel;

	if ((unsigned)x >= (unsigned)data->width || (unsigned)y >= (unsigned)data->height)
		return ;
	pixel = data->img->addr + ((size_t)y * data->img->line_len
			+ (size_t)x * (data->img->bpp >> 3));
	*(unsigned int *)pixel = color;
}

int draw_background(t_datagame *data)
{
	int y;
	int x;
	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(data, x, y, data->ceiling_color);
			x++;
		}
		y++;
	}
	while(y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(data, x,  y, data->floor_color);
			x++;
		}
		y++;
	}
	return (SUCCESS);
}