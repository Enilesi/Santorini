#include <stdio.h>
#include <stdint.h>

void pack(uint64_t i, unsigned char *b) {
    b[0] = i & 0xFF;
    b[1] = (i >> 8) & 0xFF;
    b[2] = (i >> 16) & 0xFF;
    b[3] = (i >> 24) & 0xFF;
    b[4] = (i >> 32) & 0xFF;
    b[5] = (i >> 40) & 0xFF;
    b[6] = (i >> 48) & 0xFF;
    b[7] = (i >> 56) & 0xFF;
}

uint64_t unpack(const unsigned char *b) {
    return ((uint64_t)b[0]) |
           ((uint64_t)b[1] << 8) |
           ((uint64_t)b[2] << 16) |
           ((uint64_t)b[3] << 24) |
           ((uint64_t)b[4] << 32) |
           ((uint64_t)b[5] << 40) |
           ((uint64_t)b[6] << 48) |
           ((uint64_t)b[7] << 56);
}

int main() {
    uint64_t original = 12345678901234567890ULL;
    unsigned char packed[8];

    pack(original, packed);

    uint64_t unpacked = unpack(packed);

    printf("Original: %lu\n", original);
    printf("Unpacked: %lu\n", unpacked);

    return 0;
}
