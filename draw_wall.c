#include "header.h"


static t_img *get_wall_texture(t_datagame *data)
{
    if (data->ray.side == 0)
    {
        if (data->ray.ray_dir_x > 0)
            return (&data->east_tex);
        else
            return (&data->west_tex);
    }
    else
    {
        if (data->ray.ray_dir_y > 0)
            return (&data->south_tex);
        else
            return (&data->north_tex);
    }
}

static int calculate_tex_x(t_datagame *data, t_img *texture)
{
    double  wall_x;
    int     tex_x;

    if (data->ray.side == 0)
        wall_x = data->pos_y + data->ray.dist_wall * data->ray.ray_dir_y;
    else
        wall_x = data->pos_x + data->ray.dist_wall * data->ray.ray_dir_x;
    wall_x = wall_x - floor(wall_x);
    tex_x = (int)(wall_x * (double)texture->width);
    if (data->ray.side == 0 && data->ray.ray_dir_x < 0)
        tex_x = texture->width - tex_x - 1;
    if (data->ray.side == 1 && data->ray.ray_dir_y > 0)
        tex_x = texture->width - tex_x - 1;
    return (tex_x);
}

static void render_wall_stripe(t_datagame *data, t_img *texture, int x, int tex_x)
{
    double  step;
    double  tex_pos;
    int     y;
    int     tex_y;
    int     color;

    step = 1.0 * texture->height / data->ray.line_height;
    tex_pos = (data->ray.startdraw - HEIGHT / 2 + data->ray.line_height / 2) * step;
    y = data->ray.startdraw;
    while (y <= data->ray.enddraw)
    {
        tex_y = (int)tex_pos;
        tex_pos += step;
        color = get_texture_color(texture, tex_x, tex_y);
        if (data->ray.side == 1)
            color = (color >> 1) & 8355711;
        put_pixel(data, x, y, color);
        y++;
    }
}

void draw_wall_column(t_datagame *data, int x)
{
    t_img   *texture;
    int     tex_x;

    texture = get_wall_texture(data);
    tex_x = calculate_tex_x(data, texture);
    render_wall_stripe(data, texture, x, tex_x);
}
