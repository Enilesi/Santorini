#include <stdio.h>
#define PINK_HIGHLIGHT "\033[48;2;255;64;163m%s\033[m"
#define BLUE_HIGHLIGHT "\033[48;2;0;158;254m%s\033[m"
#define GREEN_HIGHLIGHT "\033[48;2;0;204;0m%s\033[m"

int main() {
    // ANSI escape code to start black text with magenta highlight
    printf("\033[1;30;45m"); // 1 is for bold, 30 is for black text color, 45 is for magenta highlight

    // Print the text
    printf("This text has black color with magenta highlight!\n");

    // Reset color to default (0)
    printf("\033[0m"); // ANSI escape code to reset colors
    
    // ANSI escape code to start black text with green highlight
    printf("\033[1;30;42m"); // 1 is for bold, 30 is for black text color, 42 is for green highlight

    // Print the text
    printf("This text has black color with green highlight!\n");

    // Reset color to default (0)
    printf("\033[0m"); // ANSI escape code to reset colors
     printf("\033[1;30;46m"); // 1 is for bold, 30 is for black text color, 46 is for cyan highlight

    // Print the text
    printf("This text has black color with cyan highlight!\n");

    // Reset color to default (0)
    printf("\033[0m"); // ANSI escape code to reset colors

  printf ("\033[48:2:255:165:0m%s\033[m\n","Hello world");
    printf ("\033[48;2;255;165;0m%s\033[m\n\n\n","Hello world");

    printf(PINK_HIGHLIGHT"\n", "Hello world");
    printf(BLUE_HIGHLIGHT"\n", "Hello world");
    printf(GREEN_HIGHLIGHT"\n", "Hello world");

    printf("\033[48;2;190;64;240m%s\033[m\n", "Hello world");



    return 0;
}
