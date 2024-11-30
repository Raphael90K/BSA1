#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <x86intrin.h>

#define NUM_ITERATIONS 1000000

static inline uint64_t get_tsc() {
    return __rdtsc();
}


int main() {
    pid_t pid;
    uint64_t start_tsc, end_tsc;
    uint64_t latency_in_ticks, avg_latency_in_ticks;
    struct timespec req = {0, 0};

    start_tsc = get_tsc();
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        nanosleep(&req, NULL);
    }
    end_tsc = get_tsc();

    latency_in_ticks = end_tsc - start_tsc;
    avg_latency_in_ticks = latency_in_ticks / NUM_ITERATIONS;

    printf("avg time for nanosleep is %lu\n", avg_latency_in_ticks);

    return 0;
}
