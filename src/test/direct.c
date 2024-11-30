#include <unistd.h>     // Für syscall()
#include <fcntl.h>       // Für die O_-Konstanten
#include <stdio.h>       // Für perror()

int main() {
    // Datei öffnen oder erstellen
    int fd = syscall(SYS_open, "output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // String, der geschrieben werden soll
    const char *message = "Hallo, System Call!\n";
    size_t length = 20; // Länge der Nachricht

    // In die Datei schreiben
    ssize_t bytes_written = syscall(SYS_write, fd, message, length);
    if (bytes_written == -1) {
        perror("write");
        syscall(SYS_close, fd); // Sicherstellen, dass die Datei geschlossen wird
        return 1;
    }

    // Datei schließen
    if (syscall(SYS_close, fd) == -1) {
        perror("close");
        return 1;
    }

    return 0;
}
