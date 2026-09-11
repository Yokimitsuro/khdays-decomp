extern void func_ov107_020c9ec8(int v, void *b);
extern void func_ov107_020c6980(void *a, void *b);

void func_ov257_020cc678(char *self, void *b) {
    if (*(unsigned short *)(self + 0x1ac) & 2) {
        b = 0;
    }
    func_ov107_020c9ec8(*(int *)(self + 0x3d0), b);
    func_ov107_020c6980(self, b);
}
