#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./lexer/lexer.h"

void printLogo() {
    printf("\033[1;36m");
    printf(
        "             ___\n"
        "          .=\"   \"=._.---.\n"
        "        .\"         c ' Y'`p\n"
        "       /   ,       `.  w_/    _    __  __ ____   \n"
        "       |   '-.   /     /     / \\  |  \\/  | __ ) \n"
        " _,..._|      )_-.\\ \\_=\\.\\  / _ \\ | |\\/| |  _ \\   \n"
        "`-....-'`------)))`=-'\"`'\" / ___ \\| |  | | |_) |\n"
        "                          /_/   \\_\\_|  |_|____/ \n"
    );
    printf("\033[0m\n\n"); 
}

void compiler(const char* source) {
    printf("Compiling project: %s\n", source);
    FILE *file = fopen(source, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", source);
        return;
    }
    analyzeFile(file);
    fclose(file);
}
int main(int argc, char *argv[]) 
{   
    printLogo();

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command> [<args>]\n", argv[0]);
        fprintf(stderr, "Commands:\n");
        fprintf(stderr, "  ambc <source>       Compile a C project\n");
    }

    const char* command = argv[1];

    if (strcmp(command, "ambc") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Usage: %s ambc <source>\n", argv[0]);
            return 1;
        }
        compiler(argv[2]);
    } else {
        fprintf(stderr, "Unknown command: %s\n", command);
        fprintf(stderr, "Commands:\n");
        fprintf(stderr, "  ambc <source>       Compile a C project\n");
    }

    return 0;
}