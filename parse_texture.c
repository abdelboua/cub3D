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


int parse_map(char *first_line,int fd, t_datagame *data)
{
	t_list *map_list;
	t_list *current;
	t_list *new_node;
	char *next_line;
	int i;

	i = 0;

	map_list = ft_lstnew(first_line);
	if (!map_list)
	{
		free(first_line);
		return (ERROR);
	}
	data->map_height = 1;

	while ((next_line = get_next_line(fd)) != NULL)
	{
		if(next_line[0] == '\n' || next_line[0] == '\0')
		{
			free(next_line);
			ft_lstclear(&map_list, free);
			return (ERROR);
		}
		new_node = ft_lstnew(next_line);
		if (!new_node)
		{
			free(next_line);
			ft_lstclear(&map_list, free);
			return(ERROR);
		}
		ft_lstadd_back(&map_list, new_node);
		data->map_height++;
	}

	data->map = malloc(sizeof(char *) * (data->map_height + 1));
	if (!data->map)
	{
		ft_lstclear(&map_list, free);
		return (ERROR);
	}
	i = 0;
	current = map_list;
	while (i < data->map_height)
	{
		data->map[i] = ft_strdup((char *)current->content);
		if(!data->map[i])
		{
			free_array(data->map);
			ft_lstclear(&map_list, free);
			return (ERROR);
		}
		current = current->next;
		i++;
	}
	data->map[data->map_height] = NULL;
	ft_lstclear(&map_list, free);
	if (valid_map(data) == ERROR)
	{
		free_array(data->map);
		return (ERROR);
	}
	return (SUCCESS);
}

