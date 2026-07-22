/* Release the object's per-row buffers. The count at +0x6a is RE-READ on every
 * iteration -- the free path can shorten the list -- and the whole thing is
 * skipped in the boot mode where bit 2 of data_0204c240 is set. */
extern void NNSi_FndFreeFromDefaultHeap(void *block);

typedef struct {
    unsigned char bFlags;   /* +0 */
} Ov002LayoutFlags;

typedef struct {
    char pad0000[0x6a];
    signed char nBuffers;   /* +0x6a */
    char pad006b[1];
    void *buffers[1];       /* +0x6c */
} Ov002RowOwner;

extern Ov002LayoutFlags data_0204c240;

void func_ov002_0207b020(Ov002RowOwner *self) {
    int i;

    if ((data_0204c240.bFlags & 4) != 0) {
        return;
    }

    i = 0;

    if (self->nBuffers > 0) {
        do {
            NNSi_FndFreeFromDefaultHeap(self->buffers[i]);
            i++;
        } while (i < self->nBuffers);
    }
}
