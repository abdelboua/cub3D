#include "./header.h"

static int	is_valid_map_char(char c)
{
    return (c == '0' || c == '1' || c == ' ' || c == 'N' 
        || c == 'S' || c == 'E' || c == 'W');
}

static int	check_player_position(t_datagame *data, int y, int x, char c)
{
    int	player_count;

    player_count = 0;
    if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
    {
        player_count = 1;
        data->player_x = x;
        data->player_y = y;
        data->player_dir = c;
		data->map[y][x] = '0';
    }
    return (player_count);
}

static int	validate_map_chars(t_datagame *data, int *player_count)
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
            if (!is_valid_map_char(c))
                return (ERROR);
            *player_count += check_player_position(data, y, x, c);
            x++;
        }
        y++;
    }
    return (SUCCESS);
}

int	valid_map(t_datagame *data)
{
    int	player_count;

    player_count = 0;
    if (validate_map_chars(data, &player_count) == ERROR)
        return (ERROR);
    if (player_count != 1)
        return (ERROR);
    if (check_walls(data) == ERROR)
        return (ERROR);
    return (SUCCESS);
}