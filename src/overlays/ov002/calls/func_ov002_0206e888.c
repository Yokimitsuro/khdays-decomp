extern unsigned short *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov002_0206e8b0(void);
/* Hand back the retry callback only while the heap's bit 1 is set. */
int func_ov002_0206e888(void) {
    int cb = 0;
    if ((*NNSi_FndGetCurrentRootHeap() & 2) > 0) {
        cb = (int)func_ov002_0206e8b0;
    }
    return cb;
}
