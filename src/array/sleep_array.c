#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <x86intrin.h>

#define NUM_ITERATIONS 1000000

static inline uint64_t get_tsc() {
    return __rdtsc();
}

int main() {
    uint64_t start_tsc, end_tsc;
    uint64_t latency_in_ticks;
    struct timespec req = {0, 0};
    long long cycles[NUM_ITERATIONS];

    FILE *logfile = fopen("../resources/latencies_nanosleep.csv", "w");
    if (!logfile) {
        perror("Fehler beim Öffnen der Log-Datei");
        return 1;
    }
    fprintf(logfile, "Messung,Latenz_tz\n");

    for (int i = 0; i < NUM_ITERATIONS; i++) {

        start_tsc = get_tsc();

        nanosleep(&req, NULL);

        end_tsc = get_tsc();

        latency_in_ticks = end_tsc - start_tsc;
        cycles[i] = latency_in_ticks;

    }
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        fprintf(logfile, "%d,%llu\n", i, cycles[i]);
    }

    fclose(logfile);

    return 0;
}
