#include "./header.h"

static int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

static int	read_remaining_map(int fd, t_list **map_list, int *height)
{
	char	*next_line;
	t_list	*new_node;

	while ((next_line = get_next_line(fd)) != NULL)
	{
		if (is_empty_line(next_line))
		{
			free(next_line);
			ft_lstclear(map_list, free);
			return (ERROR);
		}
		new_node = ft_lstnew(next_line);
		if (!new_node)
		{
			free(next_line);
			ft_lstclear(map_list, free);
			return (ERROR);
		}
		ft_lstadd_back(map_list, new_node);
		(*height)++;
	}
	return (SUCCESS);
}

static char	*copy_line(char *line)
{
	int		len;
	char	*copy;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		len--;
	copy = malloc(len + 1);
	if (!copy)
		return (NULL);
	ft_strlcpy(copy, line, len + 1);
	return (copy);
}

static int	list_map(t_datagame *data, t_list *map_list)
{
	t_list	*current;
	int		i;

	data->map = malloc(sizeof(char *) * (data->map_height + 1));
	if (!data->map)
		return (ERROR);
	i = 0;
	current = map_list;
	while (i < data->map_height)
	{
		data->map[i] = copy_line((char *)current->content);
		if (!data->map[i])
		{
			free_array(data->map);
			return (ERROR);
		}
		current = current->next;
		i++;
	}
	data->map[data->map_height] = NULL;
	return (SUCCESS);
}

int	parse_map(char *first_line, int fd, t_datagame *data)
{
	t_list	*map_list;

	map_list = ft_lstnew(first_line);
	if (!map_list)
	{
		free(first_line);
		return (ERROR);
	}
	data->map_height = 1;
	if (read_remaining_map(fd, &map_list, &data->map_height) == ERROR)
		return (ERROR);
	if (list_map(data, map_list) == ERROR)
	{
		ft_lstclear(&map_list, free);
		return (ERROR);
	}
	ft_lstclear(&map_list, free);
	if (valid_map(data) == ERROR)
	{
		free_array(data->map);
		return (ERROR);
	}
	return (SUCCESS);
}
