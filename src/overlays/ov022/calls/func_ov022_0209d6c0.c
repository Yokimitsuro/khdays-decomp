extern void func_ov022_020ad8e0(int obj, int mode);
extern void func_ov022_020a35f4(int obj, int mode);

void func_ov022_0209d6c0(int obj) {
    func_ov022_020ad8e0(obj, 0);
    if ((*(unsigned int *)(obj + 0x24) & 4) != 0) {
        if ((int)*(unsigned int *)(obj + 0x480) <= 0 &&
            *(unsigned int *)(obj + 0x58) == 0x80000000) {
            *(unsigned long long *)obj &= ~0x2000000LL;
            func_ov022_020a35f4(obj, 4);
            return;
        }
        *(unsigned long long *)obj |= 0x2000000LL;
        func_ov022_020a35f4(obj, 5);
        return;
    }
    if (*(unsigned int *)(obj + 0x480) != 0) {
        *(unsigned long long *)obj |= 0x2000000LL;
    } else {
        *(unsigned long long *)obj &= ~0x2000000LL;
        *(int *)(obj + 0x58) = 0x400;
    }
    func_ov022_020a35f4(obj, 5);
}
