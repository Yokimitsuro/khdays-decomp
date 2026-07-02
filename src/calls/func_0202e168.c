extern void func_0202e0ec();
void func_0202e168(int *p, int v) {
    p[0] = 0;
    p[2] = v;
    p[4] = 0;
    *(unsigned char *)((char *)p + 0x18) = 0x7f;
    p[1] = 0x1000;
    p[5] = 0;
    func_0202e0ec(p, v);
}
