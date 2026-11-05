/* Allocates a class instance (0x2c bytes) from the class heap and runs its constructor with the
 * descriptor and the argument. Returns the new instance. */

#include "game/heap.h"

extern void *gMainHeap;
extern int *RunClassConstructor(void *ptr, int arg1, int arg2);

int *InstantiateClass(int arg1, int arg2) {
    void *ptr = AllocFromExpHeapWrapper(0x2c, gMainHeap);

    return RunClassConstructor(ptr, arg1, arg2);
}
