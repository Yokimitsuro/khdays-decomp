extern char *NNSi_FndGetCurrentRootHeap(void);
extern int func_02030670(void);
extern void func_ov105_020bd59c(int a, int b, int c);
extern void func_02023728(int a, int b);
extern int data_0204c22c;
extern int data_0204c024;

/* Closes the debug overlay if it is up: stops its task (only while the gate is open) and frees
 * the window. The "up" flag is cleared either way. */
void func_020309f0(void) {
    char *heap = NNSi_FndGetCurrentRootHeap();
    if (data_0204c22c != 0) {
        if (func_02030670() != 0) {
            func_ov105_020bd59c(0xc, 0, 0);
        }
        func_02023728(*(int *)(heap + 0x5c), data_0204c024);
    }
    data_0204c22c = 0;
}
