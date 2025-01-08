#include <stdio.h>
#include <stdlib.h>

void simulate_allocation() {
    for (int i = 0; i < 10; i++) {
        void *ptr = malloc(1024 * 1024); // Allocate 1 MB
        printf("Allocated 1 MB: %p\n", ptr);
        free(ptr);
    }
}

void purge_memory() {
    // Simulate memory purging by calling free()
    // In real use, this would be triggered by the Scudo allocator's M_PURGE behavior.
    printf("Simulating memory purge...\n");
    // Freeing all memory is effectively a "purge"
    // In a real system, Scudo would handle this.
}

int main() {
    simulate_allocation();
    purge_memory();
    return 0;
}
