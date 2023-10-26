#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char *file_option = NULL;
    int number_option = 1;

    struct option long_options[] = {
        {"file", required_argument, 0, 'f'},
        {"number", required_argument, 0, 'n'},
        {0, 0, 0, 0}
    };

    int c;
    while ((c = getopt_long(argc, argv, "f:n:", long_options, NULL)) != -1) {
        switch (c) {
            case 'f':
                file_option = optarg;
                break;
            case 'n':
                number_option = atoi(optarg);
                break;
        }
    }

    if (file_option) {
        setenv("FILE_NAME", file_option, 1);
    }

    char cmd[256];
    for (int i = 1; i <= number_option; i++) {
        snprintf(cmd, sizeof(cmd), "/home/vboxuser/OS/OperatingSystem/Pr5/Task4/child %d", i);
        system(cmd);
    }

    return 0;
}
