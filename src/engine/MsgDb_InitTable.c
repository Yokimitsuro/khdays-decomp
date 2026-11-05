/* Allocates and clears the message-database table (33 entries) and sets each entry's default mode.
 */

#include "game/heap.h"

extern void MI_CpuFill8(void *dst, unsigned char val, unsigned int size);

extern GameHeap *gMainHeap;
extern unsigned char *data_0204c238;

void MsgDb_InitTable(void) {
    int i;

    data_0204c238 = AllocFromExpHeapWrapper(0x294, gMainHeap);
    MI_CpuFill8(data_0204c238, 0, 0x294);

    for (i = 0; i < 0x21; i++) {
        *(int *)(data_0204c238 + i * 0x14 + 0x10) = 0x10;
    }
}
