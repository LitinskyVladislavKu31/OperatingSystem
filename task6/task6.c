#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "printVaribleValue.h"
#include "setVariableValue.h"
#include "assignVariableValue.h"
#include "deleteVarible.h"
#include "clearEnviroment.h"
extern char** environ; // Глобальний зовнішній масив оточення

void printHelp() {
    printf("Usage: environ [options]\n");
    printf("Options:\n");
    printf("  -h, --help \n");
    printf("  -i, --info <variable> \n");
    printf("  -s, --set <variable=value> \n");
    printf("  -a, --assign <variable> \n");
    printf("  -v, --value <value> \n");
    printf("  -d, --del <variable>\n");
    printf("  -c, --clear\n");
}



int main() {
    while (1) {
        char command[256];
        printf("Enter a command (h for help): ");
        fgets(command, sizeof(command), stdin);
        char* token = strtok(command, " \n");

        if (token == NULL) {
            continue;
        }

        if (strcmp(token, "h") == 0 || strcmp(token, "help") == 0) {
            printHelp();
        } else if ((strcmp(token, "i") == 0 || strcmp(token, "info") == 0)) {
            token = strtok(NULL, " \n");
            if (token != NULL) {
                char* value = getenv(token);
                if (value != NULL) {
                    printf("%s=%s\n", token, value);
                } else {
                    printf("Variable '%s' is not in the environment.\n", token);
                }
            } else {
                printf("Variable name not specified.\n");
            }
        } else if ((strcmp(token, "s") == 0 || strcmp(token, "set") == 0)) {
            token = strtok(NULL, " \n");
            if (token != NULL) {
                char* variable = strtok(token, "=");
                char* value = strtok(NULL, "=");
                if (variable != NULL && value != NULL) {
                    if (setenv(variable, value, 1) == 0) {
                        printf("Set %s=%s\n", variable, value);
                    } else {
                        printf("Failed to set %s=%s\n", variable, value);
                    }
                } else {
                    printf("Invalid format. Use 'set <variable=value>'\n");
                }
            } else {
                printf("Variable and value not specified.\n");
            }
        } else if ((strcmp(token, "a") == 0 || strcmp(token, "assign") == 0)) {
            token = strtok(NULL, " \n");
            if (token != NULL) {
                char* variable = token;
                token = strtok(NULL, " \n");
                if (token != NULL && (strcmp(token, "-v") == 0)) {
                    token = strtok(NULL, " \n");
                    if (token != NULL) {
                        char* value = token;
                        if (setenv(variable, value, 1) == 0) {
                            printf("Set %s=%s\n", variable, value);
                        } else {
                            printf("Failed to set %s=%s\n", variable, value);
                        }
                    } else {
                        printf("Value not specified.\n");
                    }
                } else {
                    printf("Use 'assign <variable> -v <value>'\n");
                }
            } else {
                printf("Variable not specified.\n");
            }
        } else if ((strcmp(token, "d") == 0 || strcmp(token, "del") == 0)) {
            token = strtok(NULL, " \n");
            if (token != NULL) {
                if (unsetenv(token) == 0) {
                    printf("Deleted %s from the environment.\n", token);
                } else {
                    printf("Failed to delete %s from the environment.\n", token);
                }
            } else {
                printf("Variable name not specified.\n");
            }
        } else if (strcmp(token, "c") == 0 || strcmp(token, "clear") == 0) {
            // Clear the entire environment
            while (*environ != NULL) {
                unsetenv(*environ);
                environ++;
            }
            printf("Cleared the entire environment.\n");
        } else if (strcmp(token, "q") == 0 || strcmp(token, "quit") == 0) {
            // Exit the program
            break;
        } else {
            printf("Unknown command: %s\n", token);
        }
    }

    return 0;
}