#include "header.h"

/*
** Fonction auxiliaire pour charger UN fichier .xpm dans une structure t_img
*/
static int	load_one_texture(t_datagame *data, t_img *texture, char *path)
{
	texture->img_ptr = mlx_xpm_file_to_image(data->mlx, path, &texture->width,
			&texture->height);
	if (texture->img_ptr == NULL)
	{
		ft_putstr_fd("Error\nFailed to load texture: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		return (ERROR);
	}
	texture->addr = mlx_get_data_addr(texture->img_ptr, &texture->bpp,
			&texture->line_len, &texture->endiant);
	if (texture->addr == NULL)
		return (ERROR);
	return (SUCCESS);
}

int	init_textures(t_datagame *data)
{
	if (load_one_texture(data, &data->north_tex, data->north_texture) == ERROR)
		return (ERROR);
	if (load_one_texture(data, &data->south_tex, data->south_texture) == ERROR)
		return (ERROR);
	if (load_one_texture(data, &data->east_tex, data->east_texture) == ERROR)
		return (ERROR);
	if (load_one_texture(data, &data->west_tex, data->west_texture) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

/*
** Lit la couleur d'un pixel (x, y) sur une image de texture
*/
int	get_texture_color(t_img *tex, int x, int y)
{
	char *pixel;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0x000000);

	pixel = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(int *)pixel);
}