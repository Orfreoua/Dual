#ifndef KEY_H
# define KEY_H

# ifdef __linux__
#  define OS 0
#  define UP 119
#  define DOWN 115
#  define LEFT 97
#  define RIGHT 100
#  define ECHAP 65307
#  define ARROW_LEFT 65361
#  define ARROW_RIGHT 65363
#  define ARROW_UP 65362
#  define ARROW_DOWN 65364
#  define ENTER 65293

# elif defined(__APPLE__)
#  define OS 1
#  define UP 13
#  define DOWN 1
#  define LEFT 0
#  define RIGHT 2
#  define ECHAP 53
#  define ARROW_LEFT 123
#  define ARROW_RIGHT 124
#  define ARROW_UP 126
#  define ARROW_DOWN 125
#  define ENTER 36
# endif

#endif