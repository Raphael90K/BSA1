#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <x86intrin.h>

#define NUM_ITERATIONS 1000000

pthread_mutex_t lock1;
pthread_mutex_t lock2;

static inline uint64_t get_tsc() {
    return __rdtsc();
}

void *thread_function1(void *arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        pthread_mutex_lock(&lock1);
        pthread_mutex_unlock(&lock2);
    }
    return NULL;
}

void *thread_function2(void *arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        pthread_mutex_lock(&lock2);
        pthread_mutex_unlock(&lock1);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    uint64_t start_tsc, end_tsc;
    uint64_t latency_in_ticks;
    uint64_t context_switch_time;

    // Initialisiere Mutexe
    pthread_mutex_init(&lock1, NULL);
    pthread_mutex_init(&lock2, NULL);

    // Sperre lock2 zu Beginn, um die Reihenfolge zu erzwingen
    pthread_mutex_lock(&lock2);

    // Starte Threads
    start_tsc = get_tsc();
    pthread_create(&thread1, NULL, thread_function1, NULL);
    pthread_create(&thread2, NULL, thread_function2, NULL);

    // Beende Threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    end_tsc = get_tsc();

    latency_in_ticks = end_tsc - start_tsc;

    context_switch_time = latency_in_ticks / (2.0 * NUM_ITERATIONS); // Zwei Kontextwechsel pro Iteration

    printf("Durchschnittliche Kontextwechselzeit: %lu\n", context_switch_time);

    // Zerstöre Mutexe
    pthread_mutex_destroy(&lock1);
    pthread_mutex_destroy(&lock2);

    return 0;
}
