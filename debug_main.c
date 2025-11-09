#include "./header.h"

int main(int ac, char **av)
{
	t_datagame data;

	if(ac != 2)
    {
        ft_putstr_fd("Error: Usage ./cub3D map.cub\n", 2);
        return (ERROR);
    }
	
	printf("Debug: Initializing data...\n");
	init_data(&data);
	
	printf("Debug: Parsing file %s...\n", av[1]);
	if(parse_file(av[1], &data) == ERROR)
	{
		printf("Debug: parse_file returned ERROR\n");
		return ERROR;
	}
	
	printf("Debug: Map parsed successfully!\n");
	printf("Debug: Map height: %d\n", data.map_height);
	printf("Debug: Player position: (%d, %d) dir: %c\n", data.player_x, data.player_y, data.player_dir);
	
	// Print the map
	printf("Debug: Map content:\n");
	for (int i = 0; i < data.map_height; i++) {
		printf("Line %d: '%s'\n", i, data.map[i]);
	}
	
	printf("Debug: Validation completed successfully!\n");
	return 0;
}
