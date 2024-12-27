
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// Structure to store number-letter mapping
typedef struct {
    char letter;
    char number[32];
} Mapping;

// Function prototypes
void remove_spaces(char *str);
int is_number(const char *str);
char generate_unique_letter(char *str, char used_letters[], int *used_count);
char *parse_and_replace_rpn(char *expression, Mapping mappings[], int *mapping_count);
void replace_letters_with_numbers(char *input, Mapping mappings[], int mapping_count);

