#include "headers.h"

void	game_loop(t_data *data)
{
	/*mlx_loop_hook(data->mlx, &raycasting, data);
	mlx_hook(data->win, 2, 1L << 0, &press_key, data);
	mlx_hook(data->win, 3, 1L << 1, &release_key, data);
	if (!OS)
		mlx_hook(data->win, 33, 1L << 5, close_window, data);
	else
		mlx_hook(data->win, 17, 0, close_window, data);*/
	mlx_loop(data->mlx);
}

int	main(int argc, char **argv)
{
	(void)argc; (void)argv;
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	data.mlx = mlx_init();
	if (!data.mlx)
	{
		fprintf(stderr, MLX_CONNECTION);
		exit(EXIT_FAILURE);
	}
	data.win = mlx_new_window(data.mlx, 100, 100, "");
	if (!data.win)
	{
		fprintf(stderr, WIN_CONNECTION);
		exit(EXIT_FAILURE);
	}
	game_loop(&data);
	return (EXIT_SUCCESS);
}