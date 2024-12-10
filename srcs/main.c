#include "headers.h"

int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	//mlx_destroy_image(data->mlx, data->img.img);
	free(data->mlx);
	exit(0);
}

void	game_loop(t_data *data)
{
	//mlx_loop_hook(data->mlx, &raycasting, data);
	//mlx_hook(data->win, 2, 1L << 0, &press_key, data);
	//mlx_hook(data->win, 3, 1L << 1, &release_key, data);
	if (!OS)
		mlx_hook(data->win, 33, 1L << 5, close_window, data);
	else
		mlx_hook(data->win, 17, 0, close_window, data);
	mlx_loop(data->mlx);
}

void	print_error(char *msg)
{
	fprintf(stderr, "%sError: %s ❌\n%s", RED BLINK, msg, RESET);
}

void	exit_error(char *msg)
{
	print_error(msg);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	(void)argc; (void)argv;
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	data.mlx = mlx_init();
	if (!data.mlx)
		exit_error(MLX_CONNECTION);
	data.win = mlx_new_window(data.mlx, 100, 100, "");
	if (!data.win)
	{
		free(data.mlx);
		exit_error(WIN_CONNECTION);
	}
	data.img.img = mlx_new_image(data.mlx, 100, 100);
	if (!data.img.img)
	{
		mlx_destroy_window(data.mlx, data.win);
		free(data.mlx);
		exit_error(IMG_CREATE);
	}
	data.img.addr = (char *)mlx_get_data_addr(data.img.img, &data.img.bpp,
			&data.img.size_line, &data.img.endian);
	game_loop(&data);
	return (EXIT_SUCCESS);
}