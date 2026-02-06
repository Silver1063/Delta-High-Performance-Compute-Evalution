#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char* argv[])
{

    const int values = 6;

    unsigned int fs_array[] = { 64, 256, 256, 1024, 1024, 1024 };
    unsigned int rs_array[] = { 32, 32, 128, 32, 128, 512 };

    FILE* results = fopen("results.csv", "a");

    clock_t ctime;
    char result[256];

    for (int i = 0; i < values; i++) {
        size_t file_size = fs_array[i] * 1000;
        size_t record_size = rs_array[i] * 1000;
        size_t num_threads = atoi(argv[1]);
        size_t memory_size = atoi(argv[2]);

        char* buffer = malloc(file_size);

        // Generate random data
        for (size_t i = 0; i < file_size; i++) {
            unsigned char byte = rand() % 256;
            buffer[i] = i % 256; // Get random value between 0 and 255 (inclusive)
        }

        FILE* dummy = fopen("dummy.bin", "w");

        for (int j = 0; j < file_size / record_size; j++) {

            // Start timing
            ctime = clock();

            // Time critical code
            fwrite(buffer + record_size * j, sizeof(char), record_size, dummy);
            fflush(dummy);

            // Finish timing
            ctime = clock() - ctime;

            // Write the result

            double time = (double)ctime / CLOCKS_PER_SEC;
            double throughput = (record_size / 1000) / (time * 1000);

            sprintf(result, "write,%lu,%lu,%lu,%lu,%f,%f\n", file_size / 1000, record_size / 1000, num_threads, memory_size, time * 1000, throughput);

            fwrite(result, sizeof(char), strlen(result) * sizeof(char), results);
            fflush(results);
        }

        freopen("dummy.bin", "r", dummy);

        for (int j = 0; j < file_size / record_size; j++) {
            char read_buffer[record_size];
            // Start timing
            ctime = clock();

            fread(buffer, sizeof(char), record_size, dummy);

            // Finish timing
            ctime = clock() - ctime;
            double time = (double)ctime / CLOCKS_PER_SEC;
            double throughput = (record_size / 1000) / (time * 1000);

            sprintf(result, "read,%lu,%lu,%lu,%lu,%f,%f\n", file_size / 1000, record_size / 1000, num_threads, memory_size, time * 1000, throughput);

            fwrite(result, sizeof(char), strlen(result) * sizeof(char), results);
            fflush(results);
        }

        free(buffer);
        fclose(dummy);
    }

    fclose(results);
}