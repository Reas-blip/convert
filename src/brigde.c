#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "brigde.h"
#include "utilities.h"

void remove_spaces(char *str) {
   char *write_ptr = str; // Pointer to place the next non-space character
   char *read_ptr = str;  // Pointer to read the string

   while (*read_ptr) {
      if (*read_ptr != ' ') {
         *write_ptr++ = *read_ptr;
      }
      read_ptr++;
   }
   *write_ptr = '\0'; // Null-terminate the modified string
}

// Function to check if a string is a number, allowing scientific notation
int is_number(const char *str) {
   if (*str == '-' || *str == '+') str++; // Handle negative or positive numbers
   if (!*str) return 0; // Empty string is not a number

   int has_digit = 0, has_exponent = 0, has_decimal = 0;

   while (*str) {
      if (isdigit(*str)) {
         has_digit = 1;
      } else if (*str == '.' && !has_decimal && !has_exponent) {
         has_decimal = 1; // Allow one decimal point before exponent
      } else if ((*str == 'e' || *str == 'E') && has_digit && !has_exponent) {
         has_exponent = 1; // Allow one exponent
         has_digit = 0; // Reset digit flag to ensure digits follow the exponent
         if (*(str + 1) == '+' || *(str + 1) == '-') str++; // Skip exponent sign
      } else {
         return 0; // Invalid character for a number
      }
      str++;
   }

   return has_digit; // Valid number must have at least one digit
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
   return '?'; // Return a placeholder if no unique letter is found
}

// Function to parse RPN, identify numbers, and replace them with unique letters
// void remove_spaces(char *str);
char* parse_and_replace_rpn(char *expression, Mapping mappings[], int *mapping_count) {
   char token[32];
   const char *delim = " "; // Tokens separated by space
   char *copy = strdup(expression); // Duplicate the input to tokenize
   char *ptr = strtok(copy, delim);

   // Dynamically allocate memory for the resulting expression
   char *result = (char *)malloc(256 * sizeof(char));
   if (result == NULL) {
      printf("Memory allocation failed\n");
      free(copy);
      return NULL;  // Return NULL if memory allocation fails
   }
   result[0] = '\0'; // Initialize the result string

   char used_letters[26] = {0}; // Track used letters
   int used_count = 0;

   while (ptr != NULL) {
      if (is_number(ptr)) {
         char unique_letter = generate_unique_letter(expression, used_letters, &used_count);
         if (unique_letter != '?') {
               snprintf(token, sizeof(token), "%c", unique_letter);
               strcat(result, token);

               // Store the mapping
               mappings[*mapping_count].letter = unique_letter;
               strncpy(mappings[*mapping_count].number, ptr, sizeof(mappings[*mapping_count].number) - 1);
               (*mapping_count)++;
         }
      } else {
         strcat(result, ptr);
      }
      strcat(result, " ");
      ptr = strtok(NULL, delim); // Get the next token
   }

   free(copy); // Free the duplicated string
   remove_spaces(result);

   return result; // Return the dynamically allocated string
}


// Function to replace letters with their corresponding numbers
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
   // ptr = result;
   printf("Replaced string: %s\n", result);
}