/* Allocate and seed a 0x18-byte link message: the two halfwords at +0x14/+0x16
 * carry the pair of ids, the word at +0xc the payload, and the three callback
 * slots at +0/+4/+8 get the default handler and two empty entries.
 *
 * The slots go through a `static inline` setter with a "skip -1" guard. Nothing
 * in this function can ever pass -1, so the guards are all dead -- but the ROM
 * carries them, materialising -1 three separate ways (mvns, subs r2,#1, mvns
 * again). That triple is the fingerprint of an inline helper expanded three
 * times; open-coding the stores emits three plain str and comes out short. */
extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned int size);
extern void func_ov002_02070ddc(void);

static inline void set_callback(void **slot, void *value) {
    if ((int)value != -1) {
        *slot = value;
    }
}

void *func_ov002_02070ecc(short idA, short idB, int payload) {
    char *msg = (char *)NNSi_FndAllocFromDefaultExpHeap(0x18);

    *(short *)(msg + 0x14) = idA;
    *(short *)(msg + 0x16) = idB;
    *(int *)(msg + 0xc) = payload;

    set_callback((void **)(msg + 0), (void *)func_ov002_02070ddc);
    set_callback((void **)(msg + 4), (void *)0);
    set_callback((void **)(msg + 8), (void *)0);

    return msg;
}
