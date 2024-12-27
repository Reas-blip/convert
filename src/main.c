#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "infix_to_rpn.h"
#include "brigde.h"
#include "utilities.h"
#include "rpn_to_infix.h"

int main(void){
   while (1){
    char expr[500];
    
    printf("\n========== RPN To Infix Converter ==========\n");
    printf("Valid characters: lowercase alphabet (a-z), +, -, *, /, ^, (, and )\n");
    printf("Please input your expression to convert: ");
    
    if (fgets(expr, 500, stdin) == NULL){
        fprintf(stderr, "Couldn't get expression\n");
        exit(EXIT_FAILURE);
    }

    if (expr[strlen(expr) - 1] != '\n'){
        fprintf(stderr, "Input too long (max 500 characters)\n");
        exit(EXIT_FAILURE);
    } else if (expr[0] == 0 || expr[0] == 10){
        fprintf(stderr, "Empty input\n");
        exit(EXIT_FAILURE);
    }
    
    if (expr[strlen(expr) - 1] != '\0'){
        expr[strlen(expr) - 1] = '\0';
    }
    
   //  printf("[1]: Convert from Reverse Polish Notation to Infix Notation\n");
   //  printf("[2]: Convert from Infix Notation to Reverse Polish Notation\n\n");
   //  printf("Your selection: ");

   //  uint8_t option = getchar();
    
   // while ((option != '1') && (option != '2')){
   //      if (option != '\n'){
   //          printf("Invalid option. Please select either '1' or '2': ");
   //      }
   //      option = getchar();
   //  }
    printf("\n");
    Mapping mappings[26];
    int mapping_count = 0;
    char *exprs = parse_and_replace_rpn(expr, mappings, &mapping_count);
   // printf(exprs); 


    if (is_valid_rpn_expr(exprs)){
        char *result = rpn_to_infix(exprs);
        printf("RPN: %s\n",exprs);
        replace_letters_with_numbers(result, mappings, mapping_count);
        printf("Infix: %s\n",result);
        free(result);

    } else if (is_valid_infix_expr(exprs)){
        char *result = infix_to_rpn(exprs);
        printf("Infix: %s\n",exprs);
        replace_letters_with_numbers(result, mappings, mapping_count);
        printf("RPN: %s\n",result);
        free(result);
    }
    else{
      print_error("Invalid RPN or Infix expression");
    }

    printf("\n");
    free(exprs);
    }
    return 0;
}
