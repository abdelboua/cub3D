#include "header.h"

void	init_keys(t_keys *keys)
{
	keys->w = 0;
	keys->s = 0;
	keys->a = 0;
	keys->d = 0;
	keys->left = 0;
	keys->right = 0;
}
int	press_key(int keycode, t_datagame *data)
{
	if (keycode == KEY_ESC)
		close_window(data);
	else if (keycode == KEY_W)
		data->key.w = 1;
	else if (keycode == KEY_S)
		data->key.s = 1;
	else if (keycode == KEY_A)
		data->key.a = 1;
	else if (keycode == KEY_D)
		data->key.d = 1;
	else if (keycode == KEY_LEFT)
		data->key.left = 1;
	else if (keycode == KEY_RIGHT)
		data->key.right = 1;
	return (0);
}

// Quand une touche est RELÂCHÉE
int	release_key(int keycode, t_datagame *data)
{
	if (keycode == KEY_W)
		data->key.w = 0;
	else if (keycode == KEY_S)
		data->key.s = 0;
	else if (keycode == KEY_A)
		data->key.a = 0;
	else if (keycode == KEY_D)
		data->key.d = 0;
	else if (keycode == KEY_LEFT)
		data->key.left = 0;
	else if (keycode == KEY_RIGHT)
		data->key.right = 0;
	return (0);
}
