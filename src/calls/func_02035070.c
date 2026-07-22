/* Releases the record held in *slot: first the pair of blocks at +0x10/+0x14 (both must
 * be present), then the record itself when its leading short is not negative.  Returns 0
 * when the slot was already empty, 1 otherwise.
 *
 * NNSi_FndFreeFromDefaultHeap is called with two arguments here; the name is one of the
 * misattributed SDK identifiers, so it is declared K&R and both call shapes are used. */
extern void NNSi_FndFreeFromDefaultHeap();

int func_02035070(int *slot) {
    int *o = (int *)*slot;
    if (o == 0) {
        return 0;
    }
    if (o[5] != 0 && o[4] != 0) {
        NNSi_FndFreeFromDefaultHeap(o[5], o[4]);
        ((int *)*slot)[5] = 0;
        ((int *)*slot)[4] = 0;
    }
    if (*(short *)*slot >= 0) {
        NNSi_FndFreeFromDefaultHeap(*slot);
        *slot = 0;
    }
    return 1;
}
