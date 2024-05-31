#include "lexer.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

bool isDelimiter(char chr) {
    return (chr == ' ' || chr == '+' || chr == '-' || chr == '*' || chr == '/' || chr == ',' || chr == ';' || chr == '%' || chr == '>' || chr == '<' || chr == '=' || chr == '(' || chr == ')' || chr == '[' || chr == ']' || chr == '{' || chr == '}');
}

bool isOperator(char chr) {
    return (chr == '+' || chr == '-' || chr == '*' || chr == '/' || chr == '>' || chr == '<' || chr == '=' || chr == '%');
}

bool isValidIdentifier(char *str) {
    if (str == NULL || str[0] == '\0')
        return false;
    if (isalpha(str[0]) || str[0] == '_') {
        for (int i = 1; str[i] != '\0'; i++) {
            if (!isalnum(str[i]) && str[i] != '_')
                return false;
        }
        return true;
    }
    return false;
}

bool isKeyword(char *str) {
    const char *keywords[] = {"if", "else", "elif", "while", "return", "int", "var", "for", "long", "short", "init", "func", "imp", "out", "in", "arr", "class"};
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return true;
        }
    }
    return false;
}

bool isInteger(char *str) {
    if (str == NULL || *str == '\0') {
        return false;
    }
    int i = 0;
    while (isdigit(str[i])) {
        i++;
    }
    return str[i] == '\0';
}

char *getSubstring(char *str, int start, int end) {
    int subLength = end - start + 1;
    char *subStr = (char *)malloc((subLength + 1) * sizeof(char));
    strncpy(subStr, str + start, subLength);
    subStr[subLength] = '\0';
    return subStr;
}

void printError(char *message, int line) {
    printf("\033[1;31mError at line %d: %s\033[0m\n", line, message);
}

void printSuccess(char *message) {
    printf("\033[1;32m%s\033[0m\n", message);
}

void analyzeFile(FILE *file) {
    char line[MAX_LENGTH];
    int lineNumber = 0;
    bool hasError = false;
    char oneLineCode[MAX_LENGTH * 100] = "";
    oneLineCode[0] = '\0';

    while (fgets(line, MAX_LENGTH, file) != NULL) {
        lineNumber++;
        int left = 0, right = 0;
        int len = strlen(line);
        while (right <= len && left <= right) {
            if (!isDelimiter(line[right]) && line[right] != '\n' && line[right] != '\0')
                right++;
            if (isDelimiter(line[right]) || line[right] == '\n' || line[right] == '\0') {
                if (left != right) {
                    char *subStr = getSubstring(line, left, right - 1);
                    if (subStr) {
                        if (isKeyword(subStr))
                            sprintf(oneLineCode + strlen(oneLineCode), "%s ", subStr);
                        else if (isInteger(subStr))
                            sprintf(oneLineCode + strlen(oneLineCode), "%s ", subStr);
                        else if (isValidIdentifier(subStr))
                            sprintf(oneLineCode + strlen(oneLineCode), "%s ", subStr);
                        else {
                            printError("Unidentified token", lineNumber);
                            hasError = true;
                            free(subStr);
                            break;
                        }
                        free(subStr);
                    }
                }
                if (isOperator(line[right]))
                    sprintf(oneLineCode + strlen(oneLineCode), "%c ", line[right]);
                else if (isDelimiter(line[right]) && line[right] != ' ')
                    sprintf(oneLineCode + strlen(oneLineCode), "%c ", line[right]);
                right++;
                left = right;
            }
        }
        if (hasError) break;
    }

    if (!hasError) {
        printSuccess("Syntax correct.");
        printf("One-line code for assembler: %s\n", oneLineCode);
    }
}