/* Destroy a list entry: unlink it, release what it owns, then release it.
 *
 * The entry is first taken out of the container's list, which lives 0xc into the object behind the
 * global. What it owns is released in two steps. The block at +8 goes back to the heap only when
 * the caller asks for it. The word at +4 is different: its top bit marks a pointer the entry
 * borrowed rather than allocated, so a marked word is only cleared while an unmarked one is freed
 * first. Then the entry itself goes.
 *
 * That word is read once into a local on purpose. The original holds it in a register across the
 * bit test, the null test and the free call, so reading the field three times would cost three
 * loads.
 *
 * Ghidra carries the layout as Ov002OwnedEntry.
 */

typedef unsigned int u32;

extern char *data_ov002_0207f608;
extern void NNS_FndRemoveListObject(void *list, void *object);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void func_ov002_02052af4(char *self, int freeOwned) {
    u32 buffer;

    NNS_FndRemoveListObject(data_ov002_0207f608 + 0xc, self);
    if (freeOwned != 0 && *(void **)(self + 8) != 0) {
        NNSi_FndFreeFromDefaultHeap(*(void **)(self + 8));
        *(void **)(self + 8) = 0;
    }
    buffer = *(u32 *)(self + 4);
    if ((buffer & 0x80000000) != 0) {
        *(u32 *)(self + 4) = 0;
    } else if (buffer != 0) {
        NNSi_FndFreeFromDefaultHeap((void *)buffer);
        *(u32 *)(self + 4) = 0;
    }
    if (self != 0) {
        NNSi_FndFreeFromDefaultHeap(self);
    }
}
