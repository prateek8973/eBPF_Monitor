#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX_ROWS 20
#define MAX_COLS 10
#define MAX_STRING_LENGTH 50

typedef struct {
    char **columns;
} Row;

typedef struct {
    Row *rows;
    int row_count;
} Table;

Table *create_table(int row_count) {
    Table *table = (Table *)malloc(sizeof(Table));
    table->rows = (Row *)malloc(row_count * sizeof(Row));
    table->row_count = row_count;

    for (int i = 0; i < row_count; i++) {
        table->rows[i].columns = (char **)malloc(MAX_COLS * sizeof(char *));
        for (int j = 0; j < MAX_COLS; j++) {
            table->rows[i].columns[j] = (char *)malloc(MAX_STRING_LENGTH * sizeof(char));
            snprintf(table->rows[i].columns[j], MAX_STRING_LENGTH, "Data_%d_%d", i, j);
        }
    }

    return table;
}

void query_table(Table *table) {
    for (int i = 0; i < table->row_count; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            printf("Row %d, Col %d: %s\n", i, j, table->rows[i].columns[j]);
            usleep(1000); // Simulate query latency
        }
    }
}

void delete_table(Table *table) {
    for (int i = 0; i < table->row_count; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            free(table->rows[i].columns[j]);
        }
        free(table->rows[i].columns);
    }
    free(table->rows);
    free(table);
}

int main() {
    printf("Simulating database workload...\n");

    // Create the database table
    Table *table = create_table(MAX_ROWS);

    // Simulate queries
    query_table(table);

    // Simulate deleting the table
    delete_table(table);

    printf("Database workload simulation complete.\n");
    return 0;
}
