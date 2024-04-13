#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <zlib.h>

#define SIZE 1024
// I must use -lz: z for zlip library
int main() {
    uint64_t original_number = 12345678901234567890ULL; //0ULL for long long
    uint64_t decompressed_number;

    
    unsigned char byte_array[sizeof(uint64_t)];
    memcpy(byte_array, &original_number, sizeof(uint64_t));  //void *memcpy(void *dest, const void *source, size_t n);


    
    unsigned char compressed_data[SIZE];
    uLongf compressed_size = SIZE;
    compress(compressed_data, &compressed_size, byte_array, sizeof(uint64_t));

   
    unsigned char decompressed_data[sizeof(uint64_t)];
    uLongf decompressed_size = sizeof(uint64_t);
    uncompress(decompressed_data, &decompressed_size, compressed_data, compressed_size);

    
    memcpy(&decompressed_number, decompressed_data, sizeof(uint64_t));

    printf("Original Number: %lu\n", original_number);
    printf("Original Size: %zu bytes\n", sizeof(original_number));
    printf("Compressed Size: %lu\n", compressed_size);
    printf("Decompressed Number: %lu\n", decompressed_number);

    return 0;
}
