#include "./header.h"

static int	parse_rgb_values(char **rgb_strings, int *rgb_values)
{
    int	i;

    i = 0;
    if (ft_strlen_array(rgb_strings) != 3)
        return (ERROR);
    while (i < 3)
    {
        if (!is_valid_number(rgb_strings[i]))
            return (ERROR);
        rgb_values[i] = ft_atoi(rgb_strings[i]);
        if (rgb_values[i] < 0 || rgb_values[i] > 255)
            return (ERROR);
        i++;
    }
    return (SUCCESS);
}

int	parse_ccolor(char *line, t_datagame *data)
{
    char	**rgb_strings;
    char	*color_part;
    int		rgb_values[3];

    color_part = line + 2;
    while (*color_part && ft_isspace(*color_part))
        color_part++;
    rgb_strings = ft_split(color_part, ',');
    if (rgb_strings == NULL)
        return (ERROR);
    if (parse_rgb_values(rgb_strings, rgb_values) == ERROR)
    {
        free_array(rgb_strings);
        return (ERROR);
    }
    free_array(rgb_strings);
    data->ceiling_color = (rgb_values[0] << 16)
        + (rgb_values[1] << 8) + rgb_values[2];
    return (SUCCESS);
}

int	parse_fcolor(char *line, t_datagame *data)
{
    char	**rgb_strings;
    char	*color_part;
    int		rgb_values[3];

    color_part = line + 2;
    while (*color_part && ft_isspace(*color_part))
        color_part++;
    rgb_strings = ft_split(color_part, ',');
    if (rgb_strings == NULL)
        return (ERROR);
    if (parse_rgb_values(rgb_strings, rgb_values) == ERROR)
    {
        free_array(rgb_strings);
        return (ERROR);
    }
    free_array(rgb_strings);
    data->floor_color = (rgb_values[0] << 16)
        + (rgb_values[1] << 8) + rgb_values[2];
    return (SUCCESS);
}
