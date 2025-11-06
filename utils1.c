#include "./header.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int ft_strlen_array(char **arr)
{
	int i;

	i = 0;
	if (!arr)
		return (0);
	while(arr[i])
		i++;
	return i;
}

void free_array(char **arr)
{
	int i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int ft_lstadd_back_new(t_list **list, void *content)
{
    t_list *new_node;

    new_node = ft_lstnew(content);
    if (!new_node)
        return (ERROR);
    ft_lstadd_back(list, new_node);
    return (SUCCESS);
}
void cleanup_data(t_datagame *data)
{
	if (data->north_texture)
        free(data->north_texture);
    if (data->south_texture)
        free(data->south_texture);
    if (data->west_texture)
        free(data->west_texture);
    if (data->east_texture)
        free(data->east_texture);
    if (data->map_firstline)
        free(data->map_firstline);
    if (data->map)
        free_array(data->map);
}

static int	is_valid_number(char *str)
{
    int	i;

    i = 0;
    while (str[i])
    {
        if (str[i] == ' ' || str[i] == '\t')
            return (0);
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

int	is_empty_line(char *line)
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