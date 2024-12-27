#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "brigde.h"

// Function to remove spaces from a string
void remove_spaces(char *str) {
    char *write_ptr = str;
    char *read_ptr = str;

    while (*read_ptr) {
        if (*read_ptr != ' ') {
            *write_ptr++ = *read_ptr;
        }
        read_ptr++;
    }
    *write_ptr = '\0';
}

// Function to check if a string is a number (supports decimal and scientific notation)
int is_number(const char *str) {
    if (*str == '-' || *str == '+') str++;  // Handle negative or positive numbers
    if (!*str) return 0;  // Empty string is not a number

    int has_digit = 0, has_exponent = 0, has_decimal = 0;

    while (*str) {
        if (isdigit(*str)) {
            has_digit = 1;
        } else if (*str == '.' && !has_decimal && !has_exponent) {
            has_decimal = 1;  // Allow one decimal point before exponent
        } else if ((*str == 'e' || *str == 'E') && has_digit && !has_exponent) {
            has_exponent = 1;  // Allow one exponent
            has_digit = 0;  // Reset digit flag to ensure digits follow the exponent
            if (*(str + 1) == '+' || *(str + 1) == '-') str++;  // Skip exponent sign
        } else {
            return 0;  // Invalid character for a number
        }
        str++;
    }

    return has_digit;  // Valid number must have at least one digit
}

// Function to generate a unique letter not already in the string
char generate_unique_letter(char *str, char used_letters[], int *used_count) {
    for (char c = 'a'; c <= 'z'; c++) {
        if (!strchr(str, c) && !strchr(used_letters, c)) {
            used_letters[*used_count] = c;
            (*used_count)++;
            return c;
        }
    }
    return '?';  // Return a placeholder if no unique letter is found
}

// Function to find numbers in an expression and replace them with unique letters
char* parse_and_replace_rpn(char *expression, Mapping mappings[], int *mapping_count) {
    char number[32];
    int index = 0;
    char result[256] = "";
    char used_letters[26] = {0};  // Track used letters
    int used_count = 0;

    // Iterate over each character in the expression
    for (int i = 0; expression[i] != '\0'; i++) {
        if (isdigit(expression[i]) || expression[i] == '.') {
            number[index++] = expression[i];  // Capture the number
        } else {
            if (index > 0) {
                number[index] = '\0';  // Null-terminate the current number string
                // Replace the number with a unique letter
                char unique_letter = generate_unique_letter(expression, used_letters, &used_count);
                if (unique_letter != '?') {
                    snprintf(result + strlen(result), sizeof(result) - strlen(result), "%c", unique_letter);
                     // Store the mapping
                     mappings[*mapping_count].letter = unique_letter;
                     snprintf(mappings[*mapping_count].number, sizeof(mappings[*mapping_count].number), "%s", number);
                     (*mapping_count)++;
                }
                index = 0;  // Reset for the next number
            }
            strncat(result, &expression[i], 1);  // Copy the non-number character to result
        }
    }

    // Handle case where the last part of the expression is a number
    if (index > 0) {
        number[index] = '\0';
        char unique_letter = generate_unique_letter(expression, used_letters, &used_count);
        if (unique_letter != '?') {
            snprintf(result + strlen(result), sizeof(result) - strlen(result), "%c", unique_letter);
            // Store the mapping
            mappings[*mapping_count].letter = unique_letter;
            snprintf(mappings[*mapping_count].number, sizeof(mappings[*mapping_count].number), "%s", number);
            (*mapping_count)++;

        }
    }
    remove_spaces(result);
    return strdup(result);  // Return the dynamically allocated string
}

// Function to replace letters with their corresponding numbers in a string
void replace_letters_with_numbers(char *input, Mapping mappings[], int mapping_count) {
    char result[256] = "";
    const char *ptr = input;

    while (*ptr) {
        int replaced = 0;
        for (int i = 0; i < mapping_count; i++) {
            if (*ptr == mappings[i].letter) {
                strcat(result, mappings[i].number);
                replaced = 1;
                break;
            }
        }
        if (!replaced) {
            strncat(result, ptr, 1);
        }
        ptr++;
    }

    printf("Replaced string: %s\n", result);
}

// int main() {
//     char *expression = "( 1 /((x^ 2 )+ 100 ))";  // Example expression
//     Mapping mappings[32];  // Array to store letter-number mappings
//     int mapping_count = 0;

//     char *parsed_expression = parse_and_replace_rpn(expression, mappings, &mapping_count);
//     printf("Parsed and replaced expression: %s\n", parsed_expression);

//     replace_letters_with_numbers(parsed_expression, mappings, mapping_count);

//     free(parsed_expression);  // Free dynamically allocated memory
//     return 0;
// }
