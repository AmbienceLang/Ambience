#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>
#include <stdio.h>

bool isDelimiter(char chr);
bool isOperator(char chr);
bool isValidIdentifier(char *str);
bool isKeyword(char *str);
bool isInteger(char *str);
char *getSubstring(char *str, int start, int end);
void printError(char *message, int line);
void printSuccess(char *message);
void analyzeFile(FILE *file);

#endif // LEXER_H