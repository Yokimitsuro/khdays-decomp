/* Equivalent, readable C. NOT byte-exact: 4B over. mwcc colors `frame` into r1
 * and `ret` into r0 where the ROM uses r0/r1, plus a different schedule of the
 * root+0x30 address materialization. Register-coloring + scheduling tie — no mwcc
 * generation matches (verify_sweep). Stub keeps the blob byte-exact. */
extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_0202fa20(void *p);
extern void func_0202f9f8(void *p);
extern int func_ov007_0204cf7c(void);
extern unsigned short data_0204c190;
extern int func_ov007_0204d2d0(void);

/* Fade the backdrop colour to black over 8 frames by writing a grey RGB555 value
 * (0x20 - frame*4 in all three channels) to palette entry 0x05000002; when done,
 * clear it, reset the counters and finalize the text object, returning cf7c. The
 * B-button (input bit 8) jumps to the fade-out (d2d0). */
int func_ov007_0204d23c(void) {
    int root = NNSi_FndGetCurrentRootHeap();
    int frame = *(int *)(root + 0x20) + 1;
    int ret = 0;

    *(int *)(root + 0x20) = frame;
    if (frame >= 8) {
        *(volatile unsigned short *)0x05000002 = 0;
        *(int *)(root + 0x20) = 0;
        *(int *)(root + 0x70) = 0;
        func_0202fa20((void *)(root + 0x30));
        func_0202f9f8((void *)(root + 0x30));
        ret = (int)func_ov007_0204cf7c;
    } else {
        unsigned short v = 0x20 - frame * 4;
        *(volatile unsigned short *)0x05000002 = v | v * 0x20 | v * 0x400;
    }
    if ((data_0204c190 & 8) != 0) {
        *(int *)(root + 0x20) = 0;
        ret = (int)func_ov007_0204d2d0;
    }
    return ret;
}
