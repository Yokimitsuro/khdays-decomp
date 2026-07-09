extern short func_02030788(void);
extern void func_0202a818(unsigned short *arg0, int arg1);
void func_ov022_0209ca88(int arg0) {
    unsigned int *p;
    if (func_02030788() != 0) return;
    p = *(unsigned int **)(arg0 + 0x20);
    if ((*p & 0x40) == 0) return;
    func_0202a818((unsigned short *)(p + 1), *(short *)(arg0 + 0x2aba));
}
