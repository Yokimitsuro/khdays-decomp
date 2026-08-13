/* Give the buffer set back and forget it.
 *
 * Two loose buffers at 0x20 and 0x24 go first, then the loop returns four pairs: the pointer at the
 * cursor and the one 0x10 further on, stepping four bytes at a time, so the front of the object is
 * two parallel arrays of four rather than an array of pairs. The audio channel is silenced, the
 * state word cleared, and the global that owned the set is nulled last.
 *
 * The counter is declared before the walking pointer, which is what settles the two into the
 * registers the original uses.
 *
 * Ghidra carries the object as Ov002BufferSet.
 */

extern char *data_ov002_0207f618;
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void func_02033bb4(int a, int b, int c);

void func_ov002_02058fbc(void) {
    char *self = data_ov002_0207f618;
    int i;
    char *slot;

    if (*(void **)(self + 0x20) != 0) {
        NNSi_FndFreeFromDefaultHeap(*(void **)(self + 0x20));
    }
    if (*(void **)(self + 0x24) != 0) {
        NNSi_FndFreeFromDefaultHeap(*(void **)(self + 0x24));
    }
    i = 0;
    slot = self;
    do {
        if (*(void **)slot != 0) {
            NNSi_FndFreeFromDefaultHeap(*(void **)slot);
        }
        if (*(void **)(slot + 0x10) != 0) {
            NNSi_FndFreeFromDefaultHeap(*(void **)(slot + 0x10));
        }
        i++;
        slot += 4;
    } while (i < 4);
    func_02033bb4(0, 8, 0xf);
    *(int *)(self + 0x30) = 0;
    data_ov002_0207f618 = 0;
}
