#include "header.h"

static void	player_move(t_datagame *data, double speed, int forward)
{
    double	new_x;
    double	new_y;

    if (forward)
    {
        new_x = data->pos_x + data->dir_x * speed;
        new_y = data->pos_y + data->dir_y * speed;
    }
    else
    {
        new_x = data->pos_x - data->dir_x * speed;
        new_y = data->pos_y - data->dir_y * speed;
    }
    if (data->map[(int)data->pos_y][(int)new_x] == '0')
        data->pos_x = new_x;
    if (data->map[(int)new_y][(int)data->pos_x] == '0')
        data->pos_y = new_y;
}

static void	player_strafe(t_datagame *data, double speed, int right)
{
    double	new_x;
    double	new_y;

    if (right)
    {
        new_x = data->pos_x + data->fov_x * speed;
        new_y = data->pos_y + data->fov_y * speed;
    }
    else
    {
        new_x = data->pos_x - data->fov_x * speed;
        new_y = data->pos_y - data->fov_y * speed;
    }
    if (data->map[(int)data->pos_y][(int)new_x] == '0')
        data->pos_x = new_x;
    if (data->map[(int)new_y][(int)data->pos_x] == '0')
        data->pos_y = new_y;
}

static void	rotate_player(t_datagame *data, double rot, int clockwise)
{
    double	old_dirx;
    double	old_fovx;
    double	angle;

    if (clockwise)
        angle = -rot;
    else
        angle = rot;
    old_dirx = data->dir_x;
    data->dir_x = data->dir_x * cos(angle) - data->dir_y * sin(angle);
    data->dir_y = old_dirx * sin(angle) + data->dir_y * cos(angle);
    old_fovx = data->fov_x;
    data->fov_x = data->fov_x * cos(angle) - data->fov_y * sin(angle);
    data->fov_y = old_fovx * sin(angle) + data->fov_y * cos(angle);
}

void	update_player(t_datagame *data)
{
    double	move_speed;
    double	rot_speed;

    move_speed = 0.05;
    rot_speed = 0.03;
    if (data->key.w == 1)
        player_move(data, move_speed, 1);
    if (data->key.s == 1)
        player_move(data, move_speed, 0);
    if (data->key.d == 1)
        player_strafe(data, move_speed, 1);
    if (data->key.a == 1)
        player_strafe(data, move_speed, 0);
    if (data->key.right == 1)
        rotate_player(data, rot_speed, 1);
    if (data->key.left == 1)
        rotate_player(data, rot_speed, 0);
}
