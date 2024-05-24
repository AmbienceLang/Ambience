#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./ambs/ambs.c"

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
    // TODO: Compilation Logic
}

void packageManager(const char* action) {
    printf("Managin packages with action: %s\n", action);
    // TODO: Package Manager Logic
}

void projectSetup() {
    printf("Starting Setup builder.\n");
    setup();
}

int main(int argc, char *argv[]) 
{   
    printLogo();

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command> [<args>]\n", argv[0]);
        fprintf(stderr, "Commands:\n");
        fprintf(stderr, "  ambc <source>       Compile a C project\n");
        fprintf(stderr, "  apm <action>        Manage packages (install, uninstall, update)\n");
        fprintf(stderr, "  ambs <name>         Setup a new project\n");
        return 1;
    }

    const char* command = argv[1];

        if (strcmp(command, "ambc") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Usage: %s ambc <source>\n", argv[0]);
            return 1;
        }
        compiler(argv[2]);
    } else if (strcmp(command, "apm") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Usage: %s apm <action>\n", argv[0]);
            return 1;
        }
        packageManager(argv[2]);
    } else if (strcmp(command, "ambs") == 0) {
        projectSetup();
    } else {
        fprintf(stderr, "Unknown command: %s\n", command);
        fprintf(stderr, "Commands:\n");
        fprintf(stderr, "  ambc <source>       Compile a C project\n");
        fprintf(stderr, "  apm <action>        Manage packages (install, uninstall, update)\n");
        fprintf(stderr, "  ambs                Setup a new project\n");
        return 1;
    }

    return 0;
}