/* Build a record via ov000_02056094, zero it (0x10 bytes), store the key/owner, register it via
 * 02011a6c, mark it active (+0xc=1) and return it. */
extern int func_ov000_02056094(int a);
extern void MI_CpuFill8(void *dst, int val, int size);
extern void func_02011a6c(int a, int b);
int func_ov000_0205677c(int a, int b, unsigned short c) {
    int obj = func_ov000_02056094(a);
    MI_CpuFill8((void *)obj, 0, 0x10);
    *(unsigned short *)(obj) = c;
    *(int *)(obj + 4) = b;
    func_02011a6c(b, obj + 8);
    *(int *)(obj + 0xc) = 1;
    return obj;
}
