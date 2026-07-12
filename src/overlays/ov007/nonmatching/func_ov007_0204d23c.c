/* Equivalent, readable C. NOT byte-exact: register-coloring tie. The ROM keeps
 * `frame` in r0 and `ret` in r1 (with a trailing `mov r0,r1`), because the B-button
 * input read at the tail clobbers r0; mwcc-139/136/2.0/dsi instead pin the return
 * value `ret` to r0 and read the input into r1 (both valid, saves the mov -> 4B short).
 * IMPROVED over the prior nonmatching: `v` is `int` (not `unsigned short`), which drops
 * a spurious lsl#16;lsr#16 truncation and makes the whole else-branch byte-exact; only
 * the r0/r1 return coloring now differs. Unreachable across 25 mwcc builds (incl. retail
 * 3.0/136) + ~8 source forms. Stub keeps the blob byte-exact. */
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
        int v = 0x20 - frame * 4;
        *(volatile unsigned short *)0x05000002 = v | v * 0x20 | v * 0x400;
    }
    if ((data_0204c190 & 8) != 0) {
        *(int *)(root + 0x20) = 0;
        ret = (int)func_ov007_0204d2d0;
    }
    return ret;
}
