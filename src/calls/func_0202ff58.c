#pragma thumb on
extern void MI_CpuFill8(void *dest, int val, int size);
extern int func_0201ef9c(char *name, int kind);
extern void func_020136b0(int *a, int *b);
/* Zero a 0xc-byte handle, bind the func_0201ef9c(name,0xe) resource at handle[2],
 * then run func_020136b0 on it. */
void func_0202ff58(unsigned int *handle, char *name) {
    MI_CpuFill8(handle, 0, 0xc);
    handle[2] = func_0201ef9c(name, 0xe);
    func_020136b0((int *)handle, (int *)handle[2]);
}
