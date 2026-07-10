extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_0202fa38(int a, int b, int c, int d, int e, int f);
extern void func_0202f9f8(void *p);
extern int func_ov007_0204d0ec(void);
extern unsigned short data_0204c190;
extern int func_ov007_0204d2d0(void);

/* Text window fade-in: on entry set the window colour to white (0x7fff) and
 * render it; each frame brighten the backdrop (grey RGB555 = frame in all
 * channels) until frame 0x20, then re-render dimmed and go to d0ec. A-press
 * (bit 1) forces the render + jump to d0ec; B-press (bit 8) -> fade-out d2d0. */
int func_ov007_0204cf7c(void) {
    int root = NNSi_FndGetCurrentRootHeap();
    int ret = 0;
    int frame;

    if (*(int *)(root + 0x20) == 0) {
        *(volatile unsigned short *)0x05000002 = 0x7fff;
        *(volatile unsigned short *)0x05000004 = 0;
        func_0202fa38(root + 0x30, 0x80, *(int *)(root + 0x70) * 0x12 + 0xe, 2, 0x14, root + 0x7c);
        func_0202f9f8((void *)(root + 0x30));
    }
    frame = *(int *)(root + 0x20) + 1;
    *(int *)(root + 0x20) = frame;
    if (frame >= 0x20) {
        func_0202fa38(root + 0x30, 0x80, *(int *)(root + 0x70) * 0x12 + 0xe, 1, 0x14, root + 0x7c);
        func_0202f9f8((void *)(root + 0x30));
        *(int *)(root + 0x20) = 0;
        ret = (int)func_ov007_0204d0ec;
    } else {
        *(volatile unsigned short *)0x05000004 = frame | frame * 0x20 | frame * 0x400;
    }
    if ((data_0204c190 & 1) != 0) {
        if (*(int *)(root + 0x20) < 0x20) {
            func_0202fa38(root + 0x30, 0x80, *(int *)(root + 0x70) * 0x12 + 0xe, 1, 0x14, root + 0x7c);
            func_0202f9f8((void *)(root + 0x30));
        }
        ret = (int)func_ov007_0204d0ec;
        *(int *)(root + 0x20) = 0xf;
    }
    if ((data_0204c190 & 8) != 0) {
        *(int *)(root + 0x20) = 0;
        ret = (int)func_ov007_0204d2d0;
    }
    return ret;
}
