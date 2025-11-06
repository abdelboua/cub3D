#include "./header.h"

int	check_neighbor(t_datagame *data, int y, int x)
{
    if (x >= (int)ft_strlen(data->map[y]))
        return (ERROR);
    if (data->map[y][x] == ' ')
        return (ERROR);
    return (SUCCESS);
}

static int	is_walkable_char(char c)
{
    return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	check_cell_neighbors(t_datagame *data, int y, int x)
{
    if (y == 0 || y == data->map_height - 1)
        return (ERROR);
    if (check_neighbor(data, y - 1, x) == ERROR)
        return (ERROR);
    if (check_neighbor(data, y + 1, x) == ERROR)
        return (ERROR);
    if (x == 0 || x == (int)ft_strlen(data->map[y]) - 1)
        return (ERROR);
    if (check_neighbor(data, y, x - 1) == ERROR)
        return (ERROR);
    if (check_neighbor(data, y, x + 1) == ERROR)
        return (ERROR);
    return (SUCCESS);
}

int	check_walls(t_datagame *data)
{
    int		y;
    int		x;
    char	c;

    y = 0;
    while (data->map[y] != NULL)
    {
        x = 0;
        while (data->map[y][x] != '\0')
        {
            c = data->map[y][x];
            if (is_walkable_char(c))
            {
                if (check_cell_neighbors(data, y, x) == ERROR)
                    return (ERROR);
            }
            x++;
        }
        y++;
    }
    return (SUCCESS);
}