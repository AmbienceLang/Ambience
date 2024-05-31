#include "lexer.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LENGTH 100

bool isDelimiter(char chr) {
    return (chr == ' ' || chr == '+' || chr == '-' || chr == '*' || chr == '/' || chr == ',' || chr == ';' || chr == '%' || chr == '>' || chr == '<' || chr == '=' || chr == '(' || chr == ')' || chr == '[' || chr == ']' || chr == '{' || chr == '}' || chr == '!');
}

bool isOperator(char chr) {
    return (chr == '+' || chr == '-' || chr == '*' || chr == '/' || chr == '>' || chr == '<' || chr == '=' || chr == '%' || chr == '!');
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

void printError(char *message, int line, char *token) {
    printf("\033[1;31mError at line %d: %s: %s\033[0m\n", line, message, token);
}

void printSuccess(char *message) {
    printf("\033[1;32m%s\033[0m\n", message);
}

void analyzeFile(FILE *file) {
    char line[MAX_LENGTH];
    int lineNumber = 0;
    bool hasError = false;
    char *keywords[MAX_LENGTH * 100];
    char *params[MAX_LENGTH * 100];
    int keywordIndex = 0, paramIndex = 0;

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
                        if (isKeyword(subStr)) {
                            keywords[keywordIndex++] = subStr;
                            params[paramIndex++] = "";
                        } else if (isInteger(subStr) || isValidIdentifier(subStr)) {
                            params[paramIndex - 1] = subStr;
                        } else {
                            printError("Unidentified token", lineNumber, subStr);
                            hasError = true;
                            free(subStr);
                            break;
                        }
                    }
                }
                if (isOperator(line[right])) {
                    char opStr[2] = {line[right], '\0'};
                    keywords[keywordIndex++] = strdup(opStr);
                    params[paramIndex++] = "";
                }
                right++;
                left = right;
            }
        }
        if (hasError) break;
    }

    if (!hasError) {
        printSuccess("Syntax correct.");
        printf("Keywords: [");
        for (int i = 0; i < keywordIndex; i++) {
            printf("\"%s\"", keywords[i]);
            if (i < keywordIndex - 1) printf(", ");
        }
        printf("]\n");

        printf("Parameters: [");
        for (int i = 0; i < paramIndex; i++) {
            printf("\"%s\"", params[i]);
            if (i < paramIndex - 1) printf(", ");
        }
        printf("]\n");
    }

    for (int i = 0; i < keywordIndex; i++) {
        free(keywords[i]);
    }
    for (int i = 0; i < paramIndex; i++) {
        if (params[i][0] != '\0') free(params[i]);
    }
}