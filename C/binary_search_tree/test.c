// #include <ctype.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// int get_int_input(const char *prompt, int max_tries, int *result)
// {
//     int input;
//     char extra;
//     // char buffer[100];
//     char *buffer;
//     int tries = 0;

//     while (tries < max_tries)
//     {
//         printf("%s", prompt);

//         // fgets(buffer, sizeof(buffer), stdin);
//         scanf("%s", buffer);
//         printf("BUFFER LENGTH: %d\n", strlen(buffer));
//         if (strlen(buffer) > 1)
//         {
//             if (strlen(buffer) == 1 && buffer[0] == '\n')
//             {
//                 printf("Invalid input. Try again.\n");

//                 tries++;
//                 continue;
//             }
//             if (strlen(buffer) == 2 && buffer[strlen(buffer) - 1] == '\n')
//             {
//                 int num = 0;
//                 int valid = 1;

//                 for (int i = 0; buffer[i] != '\0'; i++)
//                 {
//                     if (isdigit(buffer[i]))
//                     {
//                         num = num * 10 + atoi((char)buffer[i]);
//                     }
//                     else
//                     {
//                         valid = 0;
//                         break;
//                     }
//                 }

//                 if (valid)
//                 {
//                     *result = num;
//                     return 1;
//                 }
//             }
//         }
//         // char ch = getchar();

//         // if (!(ch == '\n'))
//         // {
//         //     ungetc(ch, stdin); // put the extracted character back into input buffer

//         //     if (scanf("%d%c", &input, &extra) == 2 && extra == '\n')
//         //     {
//         //         *result = input;
//         //         return 1; // SUCCESS
//         //     }

//         //     // Clear input buffer
//         //     while (getchar() != '\n')
//         //         ;
//         // }

//         printf("Invalid input. Try again.\n");

//         tries++;
//     }

//     printf("\nMaximum tries exceeded! Please try again...\n");
//     return 0; // FAILURE
// }

// int main(void)
// {
//     int result;
//     printf("%d\n", get_int_input("Enter a number: ", 5, &result));
//     printf("%d\n", result);
//     return 0;
// }