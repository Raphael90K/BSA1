#include <stdio.h>
#include <stdlib.h>

int main() {
    // Dateiname definieren
    const char *filename = "output.txt";

    // Datei zum Schreiben öffnen
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Fehler beim Öffnen der Datei");
        return EXIT_FAILURE;
    }

    // Den Text "Hallo" in die Datei schreiben
    const char *text = "Hallo\n";
    if (fprintf(file, "%s", text) < 0) {
        perror("Fehler beim Schreiben in die Datei");
        fclose(file);
        return EXIT_FAILURE;
    }

    printf("Der Text wurde erfolgreich in die Datei '%s' geschrieben.\n", filename);

    // Datei schließen
    fclose(file);

    return EXIT_SUCCESS;
}
