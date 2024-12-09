#include "headers.h"

/*void	game_loop(t_data *data)
{
	mlx_loop_hook(data->mlx, &raycasting, data);
	mlx_hook(data->win, 2, 1L << 0, &press_key, data);
	mlx_hook(data->win, 3, 1L << 1, &release_key, data);
	if (!OS)
		mlx_hook(data->win, 33, 1L << 5, close_window, data);
	else
		mlx_hook(data->win, 17, 0, close_window, data);
	mlx_loop(data->mlx);
}

int	main(int argc, char **argv)
{
	t_data	data;

	bzero(&data, sizeof(t_data));
	if (argc != 2)
		return (print_error(BAD_NB_ARG));
	if (load_fole(&data, argv[1]) == ERROR)
		return (EXIT_FAILLURE);
	all_in_struct(&data);
	setting(&data);
	game_loop(&data);
	return (EXIT_SUCCESS);
}*/

int main(void)
{
    void *mlx;
    void *win;

    // Initialisation de la connexion avec le serveur graphique
    mlx = mlx_init();
    
    // Création d'une fenêtre de taille 800x600
    win = mlx_new_window(mlx, 800, 600, "Test MiniLibX");

    // Remplissage de la fenêtre avec une couleur (par exemple, un fond rouge)
    mlx_clear_window(mlx, win);
    mlx_string_put(mlx, win, 100, 100, 0xFFFFFF, "Bienvenue dans MiniLibX!");

    // Dessiner un rectangle (x, y, largeur, hauteur, couleur)
    //mlx_rectangle(mlx, win, 200, 200, 400, 100, 0x00FF00);

    // Attendre que l'utilisateur ferme la fenêtre
    mlx_loop(mlx);

    return 0;
}
