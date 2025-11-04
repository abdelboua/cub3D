#include "./header.h"

void init_data(t_datagame *data)
{
	data->north_texture = NULL;
	data->south_texture = NULL;
	data->west_texture = NULL;
	data->east_texture = NULL;
	data->map_firstline = NULL;
	data->map = NULL;
	data->floor_color = -1;
	data->ceiling_color = -1;
	data->map_height = 0;
	data->map_width = 0;
	data->player_x = -1;
	data->player_y = -1;
	data->player_dir = 0;
	data->config_elements_read = 0;
	data->mlx = NULL;
	data->win = NULL;
	data->img = NULL;
}
