extern int data_ov070_020b9ca0;
extern int func_02030788(void);
extern int func_ov022_020912d8(int x);
extern int func_ov022_020a35f4(int this, int tag);

int func_ov070_020b9000(int this, int param2) {
    int base = data_ov070_020b9ca0 + 0x2c2c;
    int result = 0;
    int ok = 1;

    if (func_02030788() == 0) {
        *(unsigned long long *)(this + 0x464) |= 0x10000ULL;
    }
    if (func_02030788() == 0) {
        *(unsigned long long *)(this + 0x46c) |= 0x10000ULL;
    }
    *(int *)(base + 4) = 0;
    *(int *)base = param2;
    if (param2 != 0) {
        if (func_ov022_020912d8(*(int *)(this + 0x2644) + 0x30) == 0 ||
            func_ov022_020912d8(*(int *)(this + 0x2644) + 0x60) == 0) {
            ok = 0;
        }
    }
    if (ok != 0) {
        result = func_ov022_020a35f4(this, 0x21);
    }
    return result;
}
