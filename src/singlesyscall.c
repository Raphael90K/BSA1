#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *filename = "../resources/output.txt";

    FILE *file = fopen(filename, "r"); // "r" bedeutet "lesen"
    if (file == NULL) {
        return EXIT_FAILURE;
    }

    printf("Datei '%s' wurde erfolgreich geöffnet.\n", filename);

    if (fclose(file) == 0) {
    } else {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}