#ifndef APM_H
#define APM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <json-c/json.h>

#define PACKAGE_REPO_URL "https://example.com/packages"
#define PACKAGE_DIR "./packages/"

void install_package(const char *package_name);
void publish_package(const char *package_path);
void list_packages();
void read_package_json(const char *filepath, struct json_object **package_json);

#endif