/* ★ func_0202fa20 takes TWO arguments. This file declared one, and the dropped 0 is the ROM's
 * `mov r1, #0` at +0x10 -- a single 0 doing four jobs: `ret`'s initial value, the palette clear,
 * the two counter resets, AND this call's 2nd argument. Without the argument mwcc has no reason to
 * pin `ret` to r1, so it colours `ret` into r0, loses the ROM's trailing `mov r0, r1`, and comes
 * out 4 bytes short. (2026-07-17)
 *
 * This file previously carried a write-up concluding: "register-coloring tie... Unreachable across
 * 25 mwcc builds (incl. retail 3.0/136) + ~8 source forms." Twenty-five compilers were tried. It
 * was a missing parameter. Kept as a warning: the amount of effort in a nonmatching write-up says
 * nothing about whether its conclusion is right.
 *
 */

extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_0202fa20(void *p, int b);
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
        func_0202fa20((void *)(root + 0x30), 0);
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
