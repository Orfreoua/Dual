#include "headers.h"

t_size get_image_size(void *mlx, char *path)
{
    t_size size = {0, 0}; // Initialiser la taille à (0, 0)
    void *img;

    // Charger l'image XPM et récupérer ses dimensions
    img = mlx_xpm_file_to_image(mlx, path, &size.width, &size.height);
    if (!img)
    {
        fprintf(stderr, "Erreur : Impossible de charger l'image %s\n", path);
        return size; // Retourne (0, 0) en cas d'erreur
    }

    // Libérer l'image après avoir récupéré les dimensions
    mlx_destroy_image(mlx, img);

    return size; // Retourne la taille de l'image
}

void paste_resized_image(t_data *data, t_point point, t_size size, char *path)
{
    void *img;
    void *resized_img;
    int img_width, img_height;
    int *data_addr, *resized_data_addr;
    int bpp, size_line, endian;

    // Charger l'image XPM
    img = mlx_xpm_file_to_image(data->mlx, path, &img_width, &img_height);
    if (!img)
    {
        fprintf(stderr, "Erreur : Impossible de charger l'image %s\n", path);
        return;
    }

    // Accéder aux données de l'image originale
    data_addr = (int *)mlx_get_data_addr(img, &bpp, &size_line, &endian);

    // Créer une nouvelle image redimensionnée
    resized_img = mlx_new_image(data->mlx, size.width, size.height);
    if (!resized_img)
    {
        fprintf(stderr, "Erreur : Impossible de créer une nouvelle image\n");
        mlx_destroy_image(data->mlx, img);
        return;
    }

    resized_data_addr = (int *)mlx_get_data_addr(resized_img, &bpp, &size_line, &endian);

    // Redimensionner l'image
    for (int y = 0; y < size.height; y++)
    {
        for (int x = 0; x < size.width; x++)
        {
            int src_x = x * img_width / size.width;
            int src_y = y * img_height / size.height;
            resized_data_addr[y * size.width + x] = data_addr[src_y * img_width + src_x];
        }
    }

    // Coller l'image redimensionnée à la position souhaitée
    mlx_put_image_to_window(data->mlx, data->win, resized_img, point.x, point.y);

    // Libérer la mémoire de l'image originale
    mlx_destroy_image(data->mlx, img);
    mlx_destroy_image(data->mlx, resized_img);
}
