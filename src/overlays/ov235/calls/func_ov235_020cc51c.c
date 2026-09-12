extern void func_ov107_020c9ec8(int node, int flag);
extern void func_ov107_020c6980(void *a, int flag);

void func_ov235_020cc51c(char *a, int b) {
    if (*(unsigned short *)(a + 0x1ac) & 2) {
        b = 0;
    }
    func_ov107_020c9ec8(*(int *)(a + 0x3a8), b);
    func_ov107_020c6980(a, b);
}
