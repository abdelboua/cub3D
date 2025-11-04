#include "./header.h"

int	parse_texture_no(char *line, t_datagame *data)
{
	char	*path_start;

	path_start = line + 3;
	while (*path_start != '\0' && ft_isspace(*path_start))
		path_start++;
	if (*path_start == '\0')
		return (ERROR);
	data->north_texture = ft_strdup(path_start);
	if (data->north_texture == NULL)
		return (ERROR);
	return (SUCCESS);
}
int	parse_texture_so(char *line, t_datagame *data)
{
	char	*path_start;

	path_start = line + 3;
	while (*path_start != '\0' && ft_isspace(*path_start))
		path_start++;
	if (*path_start == '\0')
		return (ERROR);
	data->south_texture = ft_strdup(path_start);
	if (data->south_texture == NULL)
		return (ERROR);
	return (SUCCESS);
}
int	parse_texture_ea(char *line, t_datagame *data)
{
	char	*path_start;

	path_start = line + 3;
	while (*path_start != '\0' && ft_isspace(*path_start))
		path_start++;
	if (*path_start == '\0')
		return (ERROR);
	data->east_texture = ft_strdup(path_start);
	if (data->east_texture == NULL)
		return (ERROR);
	return (SUCCESS);
}
int	parse_texture_we(char *line, t_datagame *data)
{
	char	*path_start;

	path_start = line + 3;
	while (*path_start != '\0' && ft_isspace(*path_start))
		path_start++;
	if (*path_start == '\0')
		return (ERROR);
	data->west_texture = ft_strdup(path_start);
	if (data->west_texture == NULL)
		return (ERROR);
	return (SUCCESS);
}
