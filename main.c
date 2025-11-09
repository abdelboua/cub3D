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
int gameloop(t_datagame *data)
{
	long long timing;
	double delta_time;

	timing = current_time();
	delta_time = (timing - data->last_time) / 1000.0;
	data->last_time = timing;
	update_player(data, delta_time);
	draw_background(data);
	cast_all_rays(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img_ptr, 0, 0);
	return 0;
}
int main(int ac, char **av)
{
	t_datagame data;

	if(ac != 2)
    {
        ft_putstr_fd("Error: Usage ./cub3D map.cub\n", 2);
        return (ERROR);
    }
	init_data(&data);
	if(parse_file(av[1], &data) == ERROR)
		return ERROR;
	init_player(&data);
	data.mlx = mlx_init();
	if(data.mlx == NULL)
	{
		ft_putstr_fd("Error : Failed to initialize mlx\n", 2);
		return ERROR;
	}
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "cub3d");
	if(data.win == NULL)
	{
		ft_putstr_fd("Error : Failed to create window\n", 2);
		free(data.mlx);
		return (ERROR);
	}
    data.img = malloc(sizeof(t_img));
    if (!data.img)
        close_window(&data); 
        
    data.img->img_ptr = mlx_new_image(data.mlx, WIDTH, HEIGHT);
    if (!data.img->img_ptr)
        close_window(&data);

    data.img->addr = mlx_get_data_addr(data.img->img_ptr, &data.img->bpp, 
                                     &data.img->line_len, &data.img->endiant);
    if (!data.img->addr)
		close_window(&data);
    mlx_hook(data.win, 2, 1L<<0, press_key, &data);
	mlx_hook(data.win, 3, 1L<<1, release_key, &data);
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_loop_hook(data.mlx, gameloop, &data);
	mlx_loop(data.mlx);
}

