#include "header.h"

/*
** Initialise les données pour le rayon de la colonne 'x'
*/
void init_ray_data(t_datagame *data, int x)
{
    data->ray.camera_x = 2 * x / (double)WIDTH - 1;
    data->ray.ray_dir_x = data->dir_x + data->fov_x * data->ray.camera_x;
    data->ray.ray_dir_y = data->dir_y + data->fov_y * data->ray.camera_x;
    data->ray.map_x = (int)data->pos_x;
    data->ray.map_y = (int)data->pos_y;
    if (data->ray.ray_dir_x == 0)
        data->ray.delta_dx = 1e30;
    else
        data->ray.delta_dx = fabs(1 / data->ray.ray_dir_x);

    if (data->ray.ray_dir_y == 0)
        data->ray.delta_dy = 1e30;
    else
        data->ray.delta_dy = fabs(1 / data->ray.ray_dir_y);
}

void init_ray_step_sidedist(t_datagame *data)
{
	if (data->ray.ray_dir_x < 0)
	{
		data->ray.stepx = -1;
		data->ray.sidedist_x = (data->pos_x - data->ray.map_x) * data->ray.delta_dx;
	}
	else 
	{
		data->ray.stepx = 1;
		data->ray.sidedist_x = (data->ray.map_x + 1.0 - data->pos_x) * data->ray.delta_dx;
	}
	if (data->ray.ray_dir_y < 0)
	{
		data->ray.stepy = -1;
		data->ray.sidedist_y = (data->pos_y - data->ray.map_y) * data->ray.delta_dy;
	}
	else
	{
		data->ray.stepy = 1;
		data->ray.sidedist_y = (data->ray.map_y + 1.0 - data->pos_y) * data->ray.delta_dy;
	}
}

void perform_dda(t_datagame *data)
{
	data->ray.hit = 0;
	while (data->ray.hit == 0)
	{
		if (data->ray.sidedist_x < data->ray.sidedist_y)
		{
			data->ray.sidedist_x = data->ray.sidedist_x + data->ray.delta_dx;
			data->ray.map_x = data->ray.map_x + data->ray.stepx;
			data->ray.side = 0;
		}
		else
		{
			data->ray.sidedist_y = data->ray.sidedist_y + data->ray.delta_dy;
			data->ray.map_y = data->ray.map_y + data->ray.stepy;
			data->ray.side = 1;
		}
		if (data->map[data->ray.map_y][data->ray.map_x] == '1')
			data->ray.hit = 1;
	}
}
void calculate_wall_height(t_datagame *data)
{
	if(data->ray.side == 0)
		data->ray.dist_wall = (data->ray.map_x - data->pos_x + (1 - data->ray.stepx) / 2) / data->ray.ray_dir_x;
	else
		data->ray.dist_wall = (data->ray.map_y - data->pos_y + (1 - data->ray.stepy) / 2) / data->ray.ray_dir_y;
	if (data->ray.dist_wall > 0)
		data->ray.line_height = (int)(HEIGHT / data->ray.dist_wall);
	else
		data->ray.line_height = HEIGHT;
	data->ray.startdraw = -data->ray.line_height / 2 + HEIGHT / 2;
	if (data->ray.startdraw < 0)
		data->ray.startdraw = 0;
	data->ray.enddraw = data->ray.line_height / 2 + HEIGHT / 2;
	if (data->ray.enddraw >= HEIGHT)
		data->ray.enddraw = HEIGHT - 1;
}
void draw_wall_column(t_datagame *data, int x)
{
	int y;
	int color;
	if (data->ray.side == 0)
		color = 0x00FF0000;
	else 
		color = 0x00AA0000;
	y = data->ray.startdraw;
	while(y <= data->ray.enddraw)
	{
		put_pixel(data, x, y, color);
		y++;
	}
}
void cast_all_rays(t_datagame *data)
{
    int x;

    x = 0;
    while (x < WIDTH)
    {
        init_ray_data(data, x);
        init_ray_step_sidedist(data);
        perform_dda(data);
        calculate_wall_height(data);
        draw_wall_column(data, x);
        x++;
    }
}