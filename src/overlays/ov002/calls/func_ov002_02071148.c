/* Build a 0x24-byte handler record: four halfword parameters at +0x1c..+0x22, a
 * cleared word at +0x18, and three callback slots at +0, +4 and +8 installed
 * through the same guarded setter.
 *
 * The setter skips the sentinel -1, and because it is a `static inline` each of
 * the three expansions materialises its own -1 -- the ROM builds it three
 * DIFFERENT ways (subs from 0, subs from a fresh 0, mvns of 0), which is the
 * fingerprint of three separate inline bodies rather than one shared constant. */
extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned int size);
extern void func_ov002_02071030(void);
extern void func_ov002_020710f4(void);

static inline void set_callback(void **slot, void *value) {
    if (value != (void *)-1) {
        *slot = value;
    }
}

void *func_ov002_02071148(int a, int b, int c, int d) {
    char *obj = NNSi_FndAllocFromDefaultExpHeap(0x24);

    *(int *)(obj + 0x18) = 0;
    *(short *)(obj + 0x1c) = (short)a;
    *(short *)(obj + 0x1e) = (short)b;
    *(short *)(obj + 0x20) = (short)c;
    *(short *)(obj + 0x22) = (short)d;

    set_callback((void **)obj, (void *)&func_ov002_02071030);
    set_callback((void **)(obj + 4), 0);
    set_callback((void **)(obj + 8), (void *)&func_ov002_020710f4);
    return obj;
}
