/*
 * Tear the item container down: release each flagged item, run the teardown callback, free.
 *
 * The container header holds a teardown callback at 0, the item stride as a halfword at 0x4e,
 * the item count as a halfword at 0x50 and the array base at 0x54. Every item whose flag
 * halfword at +0x12 has bit 0 set is released through 02076a90; the callback, if present, is
 * then called with the container itself before it goes back to the default heap.
 *
 * The count, the stride and the base are all re-read from the object on every pass, which is
 * simply what writing them inline in the loop condition and body produces.
 */

typedef unsigned short u16;

extern void func_ov002_02076a90(void *item);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void func_ov002_020769f0(char *self) {
    int i;

    for (i = 0; i < *(u16 *)(self + 0x50); i++) {
        char *item = *(char **)(self + 0x54) + *(u16 *)(self + 0x4e) * i;
        if ((*(u16 *)(item + 0x12) & 1) != 0) {
            func_ov002_02076a90(item);
        }
    }
    if (*(void (**)(char *))self != 0) {
        (*(void (**)(char *))self)(self);
    }
    NNSi_FndFreeFromDefaultHeap(self);
}
