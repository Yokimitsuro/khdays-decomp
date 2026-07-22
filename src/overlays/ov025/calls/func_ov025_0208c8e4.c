/* Builds the resource path into a 0x80-byte stack buffer, opens it (mode 0xe), stores the
 * handle at +0x1b4 and hands the sub-object at +0x4d4 to func_ov002_020522c8. */
extern void OS_SPrintf(char *dst, const char *fmt, const char *arg);
extern int func_02024ee8(char *path, int a);
extern void func_ov002_020522c8(char *p, int a, int b);
extern char data_ov025_020b4c50[];
extern char data_ov025_020b4c60[];

void func_ov025_0208c8e4(char *self, int a, int b) {
    char buf[0x80];
    OS_SPrintf(buf, data_ov025_020b4c50, data_ov025_020b4c60);
    *(int *)(self + 0x1b4) = func_02024ee8(buf, 0xe);
    func_ov002_020522c8(self + 0xd4 + 0x400, a, b);
}
