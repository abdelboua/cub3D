#include "./header.h"

int	parse_ccolor(char *line, t_datagame *data)
{
	char **rgb_strings;
	char *color_part;
	int rgb_values[3];
	int i;

	i = 0;
	color_part = line + 2;
	while (*color_part && ft_isspace(*color_part))
		color_part++;
	rgb_strings = ft_split(color_part, ',');
	if (rgb_strings == NULL)
		return (ERROR);
	if (ft_strlen_array(rgb_strings) != 3)
	{
		free_array(rgb_strings);
		return (ERROR);
	}
	while (i < 3)
	{
		rgb_values[i] = ft_atoi(rgb_strings[i]);
		if (rgb_values[i] < 0 || rgb_values[i] > 255)
		{
			free_array(rgb_strings);
			return (ERROR);
		}
		i++;
	}
	free_array(rgb_strings);
	data->ceiling_color = (rgb_values[0] << 16) + (rgb_values[1] << 8) + rgb_values[2];
	return (SUCCESS);
}

int	parse_fcolor(char *line, t_datagame *data)
{
	char **rgb_strings;
	char *color_part;
	int rgb_values[3];
	int i;

	i = 0;
	color_part = line + 2;
	while (*color_part && ft_isspace(*color_part))
		color_part++;
	rgb_strings = ft_split(color_part, ',');
	if (rgb_strings == NULL)
		return (ERROR);
	if (ft_strlen_array(rgb_strings) != 3)
	{
		free_array(rgb_strings);
		return (ERROR);
	}
	while (i < 3)
	{
		if(!is_valid_number(rgb_strings[i]))
		{
			free_array(rgb_strings);
			return (ERROR);
		}
		rgb_values[i] = ft_atoi(rgb_strings[i]);
		if (rgb_values[i] < 0 || rgb_values[i] > 255)
		{
			free_array(rgb_strings);
			return (ERROR);
		}
		i++;
	}
	free_array(rgb_strings);
	data->floor_color = (rgb_values[0] << 16) + (rgb_values[1] << 8) + rgb_values[2];
	return (SUCCESS);
}
