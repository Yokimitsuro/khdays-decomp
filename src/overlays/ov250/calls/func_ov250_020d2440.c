extern int func_02023eb4();
extern int func_0203c634();

void func_ov250_020d2440(unsigned char *obj) {
    unsigned char *mid = *(unsigned char **)(obj + 4);
    if (*(unsigned char *)(*(unsigned char **)(mid + 0xc)) != 0) {
        return;
    }
    {
        unsigned char *inner = *(unsigned char **)(mid + 0);
        int base = *(int *)(inner + 0x224);
        int diff = *(int *)(inner + 0x228) - base;
        if (diff < 0) diff = -diff;
        *(int *)(mid + 0x74) = base + func_02023eb4(diff + 1);
    }
    *(unsigned char *)(*(unsigned char **)(mid + 0) + 0x1c7) = 2;
    func_0203c634(obj, *(signed char *)(obj + 0x20), 0);
}
