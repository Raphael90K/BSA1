#include <stdio.h>
#include <time.h>

#define NUM_ITERATIONS 1000000

long long get_current_time_ns() {
    struct timespec ts;
    clockF_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000000000LL + ts.tv_nsec;
}

int main() {
    long long start_time, end_time;
    long long latencies[NUM_ITERATIONS]; // Array zur Speicherung der Latenzen
    FILE *output_file;
    int i;

    output_file = fopen("latencies.txt", "w");
    if (output_file == NULL) {
        perror("Fehler beim Öffnen der Datei");
        return 1;
    }


    for (i = 0; i < NUM_ITERATIONS; i++) {
        start_time = get_current_time_ns();
        get_current_time_ns();
        end_time = get_current_time_ns();

        latencies[i] = end_time - start_time;
    }

    for (i = 0; i < NUM_ITERATIONS; i++) {
        fprintf(output_file, "%lld\n", latencies[i]);
    }

    fclose(output_file);

    long long total_time = 0;
    for (i = 0; i < NUM_ITERATIONS; i++) {
        total_time += latencies[i];
    }
    long long avg_latency_ns = total_time / NUM_ITERATIONS;
    printf("Durchschnittliche Latenz des System-Calls: %lld Nanosekunden\n", avg_latency_ns);

    return 0;
}
