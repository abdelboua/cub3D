#include "header.h"

static int	check_config(t_datagame *data, int fd)
{
	if (data->config_elements_read != 6)
	{
		close(fd);
		ft_putstr_fd("ERROR : CONFIGURATION INCOMPLET(6 ELEMENTS REQUIRED\n)",
			2);
		return (ERROR);
	}
	return (SUCCESS);
}

static int	finalize_parsing(t_datagame *data, int fd)
{
	int	status;

	if (check_config(data, fd) == ERROR)
		return (ERROR);
	status = parse_map(data->map_firstline, fd, data);
	close(fd);
	if (status == ERROR)
	{
		ft_putstr_fd("ERROR : INVALID MAP", 2);
		return (ERROR);
	}
	return (SUCCESS);
}

static int	handle_line_status(int status, char *line, int fd)
{
	if (status == LINE_MAP)
	{
		free(line);
		return (1);
	}
	if (status == PARSING_ERROR)
	{
		free(line);
		close(fd);
		ft_putstr_fd("ERROR: INVALID CONFIGURATION FILE", 2);
		return (-1);
	}
	return (0);
}

static int	process_file_lines(int fd, t_datagame *data)
{
	char	*line;
	int		status;
	int		result;

	while ((line = get_next_line(fd)) != NULL)
	{
		status = process_line(line, data);
		result = handle_line_status(status, line, fd);
		if (result == 1)
			break ;
		if (result == -1)
			return (ERROR);
		free(line);
	}
	if (line == NULL && data->map_firstline == NULL)
	{
		ft_putstr_fd("ERROR : CONFIGURATION INCOMPLETE", 2);
		close(fd);
		return (ERROR);
	}
	return (SUCCESS);
}

int	parse_file(char *filename, t_datagame *data)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("ERROR: IMPOSSIBLE TO OPEN FILE", 2);
		return (ERROR);
	}
	if (process_file_lines(fd, data) == ERROR)
		return (ERROR);
	return (finalize_parsing(data, fd));
}
