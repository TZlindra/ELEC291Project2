// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int stringToInt(char *str) {
    int result = 0;
    int sign = 1;
    int i = 0;

    // Check for negative sign
    if (str[0] == '-') {
        sign = -1;
        i++;
    }

    // Iterate through characters of the string
    for (; str[i] != '\0'; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            // Convert character to integer and add to result
            result = result * 10 + (str[i] - '0');
        } else {
            // If non-numeric character encountered, return 0
            return 0;
        }
    }

    // Apply sign
    return sign * result;
}

void splitString(const char *str, char *part1, char *part2, char *part3) {
    // Get the length of the input string
    int length = strlen(str);
    int isNegative1 = 0; // Flag for negative first number
    int isNegative2 = 0; // Flag for negative second number
    const char *ptr = str;

    //printf("str: %s\n", str);
    //printf("part1: %p\n", (void*)part1);
    //printf("part2: %p\n", (void*)part2);

    // Check if the length of the string is less than 6
    // If it is, we cannot split the string as required
    if (length < 7) {
        printf("Error: Input string is too short to split.\n");
        printf("STR: %s \r\n", str);
        return;
    }

    // Loop through the string pointer to check for negative signs
    while (*ptr != '\0') {
        if (*ptr == '-') {
            // Check if the negative sign is for the first or second number
            if (ptr == str) {
                isNegative1 = 1;
            } else {
                isNegative2 = 1;
            }
        }
        ptr++;
    }

    // If the number was negative, prepend '-' to part1 or append it to part2
    if (isNegative1) {
        // Copy the first three characters of the input string to part1
        strncpy(part1+1, str+1, 3);
        part1[4] = '\0'; // Null-terminate the string
        part1[0] = '-'; // Prepend '-'
    } else {
        strncpy(part1, str, 3);
        part1[3] = '\0'; // Null-terminate the string
    }

    if (isNegative2) {
        // Copy the first three characters of the input string to part1
        strncpy(part2+1, str+length-4, 3);
        part2[4] = '\0'; // Null-terminate the string
        part2[0] = '-'; // Prepend '-'
    } else {
        // Copy the first three characters of the input string to part1
        strncpy(part2, str+length-4, 3);
        part2[3] = '\0'; // Null-terminate the string
    }

    //printf("part 1: %s\n", part1);
    //printf("part 2: %s\n", part2);
}

void Trim(char *str, int *xin, int *yin, int *zyn) {
    int i, j;
    char * strStart = str;
    char *x = malloc(5 * sizeof(char));
    char *y = malloc(5 * sizeof(char));
    char *z = malloc(sizeof(char));

    for (i = 0, j = 0; str[i] != '\0'; i++) {
        if (isdigit(str[i]) || str[i] == '-') {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';  // Null-terminate the resulting string
   // printf("%p \n", x);
    //printf("%s \n", str);
    //printf("%p \n", &x);
    splitString(str, x, y, z);

    //printf("%p \n", y);
    //printf("%p \n", x);

    *xin = stringToInt(x);
    *yin = stringToInt(y);
    *zyn = stringToInt(z);

    //printf("%d \n", *xin);

   // printf("%d \n", *yin);

    free(x);
    free(y);
    free(z);
}