/* NONMATCHING: whole-function register-allocation tie (different callee-saved set +
 * a redundant y copy). Logic byte-exact. For the PC port. */
/* func_ov000_02059d08 -- redraw the 10 visible logo menu rows, ov000. For each row,
 * picks the highlight palette (heap+0xd144) for the selected row, else the normal one
 * (heap+0xd140), and (re)draws it at y=2+2*row via func_ov000_02056884 / func_ov000_020568ac. */
extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov000_02056884(void *text, int pal, int a, int y);
extern void func_ov000_020568ac(void *text, int pal);
void func_ov000_02059d08(void) {
    short *h = (short *)NNSi_FndGetCurrentRootHeap();
    int *pb = (int *)((char *)h + 0xd000);
    short y = 2;
    int sel = h[1] - h[0];
    int i;
    for (i = 0; i < 10; i++) {
        int pal;
        if (sel == i) {
            pal = pb[0x51];
        } else {
            pal = pb[0x50];
        }
        func_ov000_02056884((char *)h + 0x10c, pal, y, y);
        func_ov000_020568ac((char *)h + 0x10c, pal);
        y += 2;
    }
}
