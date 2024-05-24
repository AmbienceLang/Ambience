#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

void create_directory(const char *dir_name) {
    #ifdef _WIN32
        mkdir(dir_name);
    #else
        mkdir(dir_name, 0777);
    #endif
}

void create_file(const char *file_name, const char *content) {
    FILE *file = fopen(file_name, "w");
    if (file) {
        fprintf(file, "%s", content);
        fclose(file);
    } else {
        fprintf(stderr, "Error creating file %s\n", file_name);
    }
}

void setup() {
    char project_name[100];
    char description[256];

    printf("Enter project name: ");
    fgets(project_name, sizeof(project_name), stdin);
    project_name[strcspn(project_name, "\n")] = '\0';

    printf("Enter project description: ");
    fgets(description, sizeof(description), stdin);
    description[strcspn(description, "\n")] = '\0';

    char dir_name[150];
    snprintf(dir_name, sizeof(dir_name), "%s", project_name);
    char meta_file[150];
    char sample_file[150];
    snprintf(meta_file, sizeof(meta_file), "%s/ambp.json", dir_name);
    snprintf(sample_file, sizeof(sample_file), "%s/main.amb", dir_name);

    create_directory(dir_name);

    char meta_content[512];
    snprintf(meta_content, sizeof(meta_content),
             "{\n"
             "    \"project-name\": \"%s\",\n"
             "    \"project-description\": \"%s\",\n"
             "    \"Dependencies\": \"%s\"\n"
             "}\n", project_name, description);
    create_file(meta_file, meta_content);

    const char *sample_content = "imp [std.io]\n\nfunc int main() {\n    out(\"Hello, World!\\n\");\n    return 0;\n}\n";
    create_file(sample_file, sample_content);

    printf("Project '%s' setup complete.\n", project_name);
}