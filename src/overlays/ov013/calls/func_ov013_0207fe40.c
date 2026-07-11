extern int func_02021980(void *a, int b);
extern void func_ov002_0206af88(int a, int b, int c, void *d);

int func_ov013_0207fe40(void *arg1, int arg2) {
    int r6 = func_02021980(arg1, arg2);
    int r7 = func_02021980(arg1, arg2 + 8);
    int buf[3];
    buf[0] = func_02021980(arg1, arg2 + 0x10);
    buf[1] = func_02021980(arg1, arg2 + 0x18);
    buf[2] = func_02021980(arg1, arg2 + 0x20);
    func_ov002_0206af88(r6 == 0 ? 1 : 0, r7, 6, buf);
    return 1;
}
