#include "header.h"

static int	process_texture(char *trimmed, t_datagame *data,
		int (*parse_func)(char *, t_datagame *))
{
	if (data->map_firstline != NULL)
	{
		free(trimmed);
		return (PARSING_ERROR);
	}
	if (parse_func(trimmed, data) == ERROR)
	{
		free(trimmed);
		return (PARSING_ERROR);
	}
	data->config_elements_read++;
	free(trimmed);
	return (LINE_CONFIG);
}

static int	process_color(char *trimmed, t_datagame *data, int is_floor)
{
	if (data->map_firstline != NULL)
	{
		free(trimmed);
		return (PARSING_ERROR);
	}
	if (is_floor)
	{
		if (data->floor_color != -1 || parse_fcolor(trimmed, data) == ERROR)
		{
			free(trimmed);
			return (PARSING_ERROR);
		}
	}
	else
	{
		if (data->ceiling_color != -1 || parse_ccolor(trimmed, data) == ERROR)
		{
			free(trimmed);
			return (PARSING_ERROR);
		}
	}
	data->config_elements_read++;
	free(trimmed);
	return (LINE_CONFIG);
}

static int	handle_map_line(char *line, char *trimmed, t_datagame *data)
{
	if (data->config_elements_read != 6)
	{
		free(trimmed);
		return (PARSING_ERROR);
	}
	data->map_firstline = ft_strtrim(line, "\n");
	if (data->map_firstline == NULL)
	{
		free(trimmed);
		return (PARSING_ERROR);
	}
	free(trimmed);
	return (LINE_MAP);
}

static int	check_texture_line(char *trimmed, t_datagame *data)
{
	if (ft_strncmp(trimmed, "NO ", 3) == 0 && data->north_texture == NULL)
		return (process_texture(trimmed, data, parse_texture_no));
	else if (ft_strncmp(trimmed, "SO ", 3) == 0 && data->south_texture == NULL)
		return (process_texture(trimmed, data, parse_texture_so));
	else if (ft_strncmp(trimmed, "WE ", 3) == 0 && data->west_texture == NULL)
		return (process_texture(trimmed, data, parse_texture_we));
	else if (ft_strncmp(trimmed, "EA ", 3) == 0 && data->east_texture == NULL)
		return (process_texture(trimmed, data, parse_texture_ea));
	else if (ft_strncmp(trimmed, "F ", 2) == 0)
		return (process_color(trimmed, data, 1));
	else if (ft_strncmp(trimmed, "C ", 2) == 0)
		return (process_color(trimmed, data, 0));
	return (-1);
}

int	process_line(char *line, t_datagame *data)
{
	char	*trimmed;
	int		result;

	trimmed = ft_strtrim(line, " \t\n\v\f\r");
	if (!trimmed)
		return (PARSING_ERROR);
	if (ft_strlen(trimmed) == 0)
	{
		free(trimmed);
		return (LINE_EMPTY);
	}
	result = check_texture_line(trimmed, data);
	if (result != -1)
		return (result);
	return (handle_map_line(line, trimmed, data));
}
