extern void func_ov107_020c9ee8();
extern void func_ov107_020c9264();
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov202_020cd898(void);

void func_ov202_020cd82c(char *obj) {
    int *state = *(int **)(obj + 4);
    unsigned int h = *(unsigned short *)(*state + 0x60);
    unsigned int masked = h & ~0xff00;
    *(unsigned short *)(*state + 0x60) =
        masked | (((((h << 0x10) >> 0x18) | 0x40) << 0x18) >> 0x10);
    func_ov107_020c9ee8(*(void **)(*state + 0x388), 0, 0, masked);
    func_ov107_020c9264(*state, 4, 0);
    func_0203c634(obj, *(signed char *)(obj + 0x20), func_ov202_020cd898);
}
