#include "./header.h"

void	init_data(t_datagame *data)
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
	init_keys(&data->key);
	data->last_time = current_time();
	ft_memset(&data->ray, 0, sizeof(t_ray));
}
/*
	dir x et y : x = - 1 vers le hayt et y le bas
	fov x et y : x vers la droite et y vers la gauche
	*/
void	init_player(t_datagame *data)
{
	data->pos_x = (double)data->player_x + 0.5;
	data->pos_y = (double)data->player_y + 0.5;
	data->dir_x = 0.0;
	data->dir_y = 0.0;
	data->fov_x = 0.0;
	data->fov_y = 0.0;
	if (data->player_dir == 'N')
	{
		data->dir_y = -1;
		data->fov_x = 0.66;
	}
	else if (data->player_dir == 'S')
	{
		data->dir_y = 1;
		data->fov_x = -0.66;
	}
	else if (data->player_dir == 'W')
	{
		data->dir_x = -1;
		data->fov_y = -0.66;
	}
	else if (data->player_dir == 'E')
	{
		data->dir_x = 1;
		data->fov_y = 0.66;
	}
}
