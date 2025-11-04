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