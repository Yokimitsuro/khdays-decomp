extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_02032710(int a, int b, int c);
extern void func_ov007_0204ce94(void *p);
extern void func_02033b24(int a, int b);
extern void func_0203255c(int a);
extern unsigned short data_0204c190;
extern int func_ov007_0204d2d0(void);
extern int func_ov007_0204d23c(void);

/* Scroll/advance the text window (+0x107c) using the sprite at +0x5ab4: kick it
 * once on entry; on A-press (input bit 1) settle it, pull the next line, and pick
 * the next handler (empty -> fade-out d2d0, else fade-backdrop d23c) + a SE.
 * B-press (bit 8) jumps to the fade-out. Always ticks the window. */
int func_ov007_0204d170(void) {
    int root = NNSi_FndGetCurrentRootHeap();
    int ret = 0;

    if (*(int *)(root + 0x20) == 0) {
        func_02032710(root + 0x107c, *(int *)(root + 0x5ab4), 1);
        *(int *)(root + 0x20) = *(int *)(root + 0x20) + 1;
    }
    if ((data_0204c190 & 1) != 0) {
        func_02032710(root + 0x107c, *(int *)(root + 0x5ab4), 0);
        *(int *)(root + 0x20) = 0;
        func_ov007_0204ce94((void *)root);
        if (*(unsigned short *)(root + 0x7c) == 0) {
            ret = (int)func_ov007_0204d2d0;
        } else {
            ret = (int)func_ov007_0204d23c;
        }
        func_02033b24(0, 0xa);
    }
    if ((data_0204c190 & 8) != 0) {
        *(int *)(root + 0x20) = 0;
        ret = (int)func_ov007_0204d2d0;
    }
    func_0203255c(root + 0x107c);
    return ret;
}
