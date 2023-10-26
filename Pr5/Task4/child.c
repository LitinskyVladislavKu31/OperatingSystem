#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s [program number]\n", argv[0]);
        return 1;
    }

    char *base_name = getenv("FILE_NAME");
    if (!base_name) {
        base_name = "default";
    }

    int program_number = atoi(argv[1]);
    char filename[256];
    snprintf(filename, sizeof(filename), "%s_%d.txt", base_name, program_number);

    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("Error opening file");
        return 1;
    }

    srand(time(NULL) ^ (getpid() << 16));
    for (int i = 0; i < program_number; i++) {
        double rand_value = (double)rand() / RAND_MAX;
        fprintf(fp, "%f\n", rand_value);
    }

    fclose(fp);
    return 0;
}
