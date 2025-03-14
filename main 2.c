#include <stdio.h>
#include <string.h>
#include <ctype.h>

// List of keywords
const char* keywords[] = {"int", "float", "if", "else", "while", "return", "for", "do", "break", "continue", "void", "char"};
const int num_keywords = sizeof(keywords) / sizeof(keywords[0]);

// Function prototypes
int isKeyword(const char* word);
int isOperator(char ch);
void lexicalAnalysis(FILE* file);

int main() {
    char filename[100];
    printf("Enter the input file name: ");
    scanf("%s", filename);

    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file '%s'.\n", filename);
        return 1;
    }

    printf("\nLexical Analysis Results:\n");
    lexicalAnalysis(file);

    fclose(file);
    return 0;
}

// Function to check if a word is a keyword
int isKeyword(const char* word) {
    for (int i = 0; i < num_keywords; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Function to check if a character is an operator
int isOperator(char ch) {
    char operators[] = "+-*/%=<>!&|";
    for (int i = 0; operators[i] != '\0'; i++) {
        if (ch == operators[i]) {
            return 1;
        }
    }
    return 0;
}

// Function to perform lexical analysis
void lexicalAnalysis(FILE* file) {
    char ch, buffer[100];
    int i = 0;

    while ((ch = fgetc(file)) != EOF) {
        // Check for identifiers and keywords
        if (isalnum(ch)) {
            buffer[i++] = ch;
        } else {
            if (i != 0) {
                buffer[i] = '\0';
                i = 0;
                if (isKeyword(buffer)) {
                    printf("Keyword: %s\n", buffer);
                } else if (isalpha(buffer[0])) {
                    printf("Identifier: %s\n", buffer);
                }
            }

            // Check for operators
            if (isOperator(ch)) {
                printf("Operator: %c\n", ch);
            }
        }
    }

    // Process the last buffer if any
    if (i != 0) {
        buffer[i] = '\0';
        if (isKeyword(buffer)) {
            printf("Keyword: %s\n", buffer);
        } else if (isalpha(buffer[0])) {
            printf("Identifier: %s\n", buffer);
        }
    }
}
