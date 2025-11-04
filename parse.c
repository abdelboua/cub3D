#include "header.h"

int	parse_file(char *filename, t_datagame *data)
{
	int		fd;
	char	*line;
	int		status;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("ERROR: IMPOSSIBLE TO OPEN FILE", 2);
		return (ERROR);
	}
	status = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		status = process_line(line, data);
		if (status == LINE_MAP)
			break ;
		if (status == PARSING_ERROR)
		{
			free(line);
			close(fd);
			ft_putstr_fd("ERROR: INVALID CONFIGURATION FILE", 2);
			return (ERROR);
		}
		free(line);
	}
	if (line == NULL && data->map_firstline == NULL)
	{
		ft_putstr_fd("ERROR : CONFIGURATION INCOMPLETE", 2);
		close(fd);
		return (ERROR);
	}
	if (data->config_elements_read != 6)
	{
		close(fd);
		ft_putstr_fd("ERROR : CONFIGURATION INCOMPLET(6 ELEMENTS REQUIRED\n)",
			2);
		return (ERROR);
	}
	status = parse_map(data->map_firstline, fd, data);
	close(fd);
	if (status == ERROR)
	{
		ft_putstr_fd("ERROR : INVALID MAP", 2);
		return (ERROR);
	}
	return (SUCCESS);
}

int	process_line(char *line, t_datagame *data)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, " \t\n\v\f\r");
	if (!trimmed)
		return (PARSING_ERROR);
	if (ft_strlen(trimmed) == 0)
	{
		free(trimmed);
		return (LINE_EMPTY);
	}
	if (ft_strncmp(trimmed, "NO ", 3) == 0)
	{
		if (data->map_firstline != NULL || data->north_texture != NULL)
		{
			free(trimmed);
			return (PARSING_ERROR);
		}
		if (parse_texture_no(trimmed, data) == ERROR)
		{
			free(trimmed);
			return (PARSING_ERROR);
		}
		data->config_elements_read++;
		free(trimmed);
		return (LINE_CONFIG);
	}
	else if (ft_strncmp(trimmed, "SO ", 3) == 0)
	{
		if (data->map_firstline != NULL || data->south_texture != NULL)
		{
			free(trimmed);
			return (PARSING_ERROR);
		}
		if (parse_texture_so(trimmed, data) == ERROR)
		{
			free(trimmed);
			return (PARSING_ERROR);
		}
		data->config_elements_read++;
		free(trimmed);
		return (LINE_CONFIG);
	}
	else if (ft_strncmp(trimmed, "WE ", 3) == 0)
	{
		if (data->map_firstline != NULL || data->west_texture != NULL)
		{
			free(trimmed);
			return (PARSING_ERROR);
		}
		if (parse_texture_we(trimmed, data) == ERROR)
		{
			free(trimmed);
			return (PARSING_ERROR);
		}
		data->config_elements_read++;
		free(trimmed);
		return (LINE_CONFIG);
	}
	else if (ft_strncmp(trimmed, "EA ", 3) == 0)
	{
		if (data->map_firstline != NULL || data->east_texture != NULL)
		{
			free(trimmed);
			return (PARSING_ERROR);
		}
		if (parse_texture_ea(trimmed, data) == ERROR)
		{
			free(trimmed);
			return (PARSING_ERROR);
		}
		data->config_elements_read++;
		free(trimmed);
		return (LINE_CONFIG);
	}
	else if (ft_strncmp(trimmed, "F ", 2) == 0)
	{
		if (data->map_firstline != NULL || data->floor_color != -1)
		{
			free(trimmed);
			return (PARSING_ERROR);
		}
		if (parse_fcolor(trimmed, data) == ERROR)
		{
			free(trimmed);
			return (PARSING_ERROR);
		}
		data->config_elements_read++;
		free(trimmed);
		return (LINE_CONFIG);
	}
	else if (ft_strncmp(trimmed, "C ", 2) == 0)
	{
		if (data->map_firstline != NULL || data->ceiling_color != -1)
		{
			free(trimmed);
			return (PARSING_ERROR);
		}
		if (parse_ccolor(trimmed, data) == ERROR)
		{
			free(trimmed);
			return (PARSING_ERROR);
		}
		data->config_elements_read++;
		free(trimmed);
		return (LINE_CONFIG);
	}
	else
	{
		if (data->config_elements_read != 6)
		{
			free(trimmed);
			return (PARSING_ERROR);
		}
		data->map_firstline = ft_strdup(line);
		if (data->map_firstline == NULL)
		{
			free(trimmed);
			return (PARSING_ERROR);
		}
		free(trimmed);
		return (LINE_MAP);
	}
}
