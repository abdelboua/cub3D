#include "./header.h"

int	close_window(t_datagame *data)
{
	if (data->img && data->img->img_ptr)
		mlx_destroy_image(data->mlx, data->img->img_ptr);
	if (data->img)
		free(data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	exit(SUCCESS);
}
int handle_escape(int keycode, t_datagame *data)
{
	if (keycode == KEY_ESC)
	{
		close_window(data);
		exit(0);
	}
	return (0);
}

int main(int ac, char **av)
{
	t_datagame data;
	if(ac != 2)
	{
		ft_putstr_fd("Error : Usage ./cub3D map.cub\n", 2);
		return (ERROR);
	}
	init_data(&data);
	if(parse_file(av[1], &data) == ERROR)
		return ERROR;
	data.mlx = mlx_init();
	if(data.mlx == NULL)
	{
		ft_putstr_fd("Error : Failed to initialize mlx\n", 2);
		return ERROR;
	}
	data.win = mlx_new_window(data.mlx, HEIGHT, WIDTH, "cub3d");
	if(data.win == NULL)
	{
		ft_putstr_fd("Error : Failed to create window\n", 2);
		free(data.mlx);
		return (ERROR);
	}
	mlx_key_hook(data.win, handle_escape, &data);
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_loop(data.mlx);
}

