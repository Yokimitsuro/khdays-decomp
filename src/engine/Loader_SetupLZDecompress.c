/* Reads an LZ-compressed file's header, allocates (or checks) the destination buffer for its
 * decompressed size and initialises the decompression context; returns the buffer. */

#include "game/heap.h"

extern int FS_ReadFile(void *file, void *buf, int size);
extern void MI_InitUncompContextLZ(void *a, void *buf, void *hdr);

void *Loader_SetupLZDecompress(char *self, void *file, int existing, int maxSize, int **heap) {
    int hdr;
    void *buf;
    unsigned size;

    FS_ReadFile(file, &hdr, 4);
    size = (unsigned)hdr >> 8;
    if (existing == 0) {
        buf = ExpHeap_AllocOrDefault(size, 0x20, (GameHeap *)heap);
    } else {
        if ((int)size > maxSize) return 0;
        buf = (void *)existing;
    }
    *(void **)(self + 0x28) = buf;
    *(unsigned *)(self + 0x2c) = size;
    MI_InitUncompContextLZ(self + 0x14, buf, &hdr);
    return buf;
}
