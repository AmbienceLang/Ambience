// lexer.c
#include <ctype.h> 
#include <stdbool.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

#define MAX_LENGTH 100

bool isDelimiter(char chr) { 
    return (chr == ' ' || chr == '+' || chr == '-'
            || chr == '*' || chr == '/' || chr == ','
            || chr == ';' || chr == '%' || chr == '>'
            || chr == '<' || chr == '=' || chr == '('
            || chr == ')' || chr == '[' || chr == ']'
            || chr == '{' || chr == '}'); 
} 

bool isOperator(char chr) { 
    return (chr == '+' || chr == '-' || chr == '*'
            || chr == '/' || chr == '>' || chr == '<'
            || chr == '=' || chr == '%'); 
} 

bool isValidIdentifier(char* str) { 
    return (str[0] != '0' && str[0] != '1' && str[0] != '2'
            && str[0] != '3' && str[0] != '4'
            && str[0] != '5' && str[0] != '6'
            && str[0] != '7' && str[0] != '8'
            && str[0] != '9' && !isDelimiter(str[0])); 
} 

bool isKeyword(char* str) {
    const char* keywords[] = { "if", "else", "elif", "while",
                               "return", "int", "var", "for",
                               "long", "short", ""};
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) { 
        if (strcmp(str, keywords[i]) == 0) { 
            return true; 
        } 
    } 
    return false; 
} 

bool isInteger(char* str) {
    if (str == NULL || *str == '\0') {
        return false;
    }
    int i = 0;
    while (isdigit(str[i])) {
        i++;
    }
    return str[i] == '\0';
}

char* getSubstring(char* str, int start, int end) { 
    int length = strlen(str); 
    int subLength = end - start + 1; 
    char* subStr = (char*)malloc((subLength + 1) * sizeof(char)); 
    strncpy(subStr, str + start, subLength); 
    subStr[subLength] = '\0'; 
    return subStr; 
}

int lexicalAnalyzerFromFile(FILE *file) {
    char line[MAX_LENGTH];
    while (fgets(line, MAX_LENGTH, file) != NULL) {
        int left = 0, right = 0; 
        int len = strlen(line); 
        while (right <= len && left <= right) { 
            if (!isDelimiter(line[right])) 
                right++; 
  
            if (isDelimiter(line[right]) && left == right) { 
                if (isOperator(line[right])) 
                    printf("Token: Operator, Value: %c\n", 
                           line[right]); 
  
                right++; 
                left = right; 
            } 
            else if (isDelimiter(line[right]) && left != right 
                     || (right == len && left != right)) { 
                char* subStr = getSubstring(line, left, right - 1); 
  
                if (isKeyword(subStr)) 
                    printf("Token: Keyword, Value: %s\n", 
                           subStr); 
  
                else if (isInteger(subStr)) 
                    printf("Token: Integer, Value: %s\n", 
                           subStr); 
  
                else if (isValidIdentifier(subStr) 
                         && !isDelimiter(line[right - 1])) 
                    printf("Token: Identifier, Value: %s\n", 
                           subStr); 
  
                else if (!isValidIdentifier(subStr) 
                         && !isDelimiter(line[right - 1])) 
                    printf("Token: Unidentified, Value: %s\n", 
                           subStr); 
                left = right; 
            } 
        } 
    }
    return 0; 
}
