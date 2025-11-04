#include "./header.h"

int	valid_map(t_datagame *data)
{
	int		y;
	int		x;
	int		player_count;
	char	c;

	y = 0;
	x = 0;
	player_count = 0;
	while (data->map[y] != NULL)
	{
		x = 0;
		while (data->map[y][x] != '\0')
		{
			c = data->map[y][x];
			if (c != '0' && c != '1' && c != ' ' && c != 'N' && c != 'S'
				&& c != 'E' && c != 'W')
				return (ERROR);
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				player_count++;
				data->player_x = x;
				data->player_y = y;
				data->player_dir = c;
			}
			x++;
		}
		y++;
	}
	if (player_count != 1)
		return (ERROR);
	if (check_walls(data) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	check_neighbor(t_datagame *data, int y, int x)
{
	if (x >= ft_strlen(data->map[y]))
		return (ERROR);
	if (data->map[y][x] == ' ')
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
			if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				if (y == 0)
					return (ERROR);
				if (check_neighbor(data, y - 1, x) == ERROR)
					return (ERROR);
				if (y == data->map_height - 1)
					return (ERROR);
				if (check_neighbor(data, y + 1, x) == ERROR)
					return (ERROR);
				if (x == 0)
					return (ERROR);
				if (check_neighbor(data, y, x - 1) == ERROR)
					return (ERROR);
				if (x == ft_strlen(data->map[y]) - 1)
					return (ERROR);
				if (check_neighbor(data, y, x + 1) == ERROR)
					return (ERROR);
			}
			x++;
		}
		y++;
	}
	return (SUCCESS);
}

int	parse_map(char *first_line, int fd, t_datagame *data)
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
		if (next_line[0] == '\n' || next_line[0] == '\0')
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
			return (ERROR);
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
		if (!data->map[i])
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
