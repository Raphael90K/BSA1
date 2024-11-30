#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <x86intrin.h>

#define NUM_ITERATIONS 1000000

static inline uint64_t get_tsc() {
    return __rdtsc();
}


int main() {
    pid_t pid;
    uint64_t start_tsc, end_tsc;
    uint64_t latency_in_ticks, avg_latency_in_ticks;

    start_tsc = get_tsc();
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        get_tsc();
    }
    end_tsc = get_tsc();

    latency_in_ticks = end_tsc - start_tsc;
    avg_latency_in_ticks = latency_in_ticks / NUM_ITERATIONS;

    printf("avg time for rdtsc is %lu\n", avg_latency_in_ticks);

    return 0;
}
