#ifndef ANSI_COLORS_H
#define ANSI_COLORS_H

// Reset
#define RESET "\033[0m" // Reset text color and style

// Text colors (foreground)
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

// Background colors
#define BG_BLACK "\033[40m"
#define BG_RED "\033[41m"
#define BG_GREEN "\033[42m"
#define BG_YELLOW "\033[43m"
#define BG_BLUE "\033[44m"
#define BG_MAGENTA "\033[45m"
#define BG_CYAN "\033[46m"
#define BG_WHITE "\033[47m"

// Styles
#define BOLD "\033[1m"      // Bold text
#define UNDERLINE "\033[4m" // Underlined text
#define BLINK "\033[5m"     // Blinking text
#define REVERSE "\033[7m"   // Reverse background and foreground colors
#define INVISIBLE "\033[8m" // Invisible text

#endif // ANSI_COLORS_H