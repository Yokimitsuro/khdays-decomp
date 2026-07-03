extern void func_ov082_020b8a10(void *this);
extern void func_ov082_020b9210(void *this);
extern void func_ov082_020b9168(void *this);

void func_ov082_020ba0e4(char *this, int cmd) {
    char *g = *(char **)(this + 0xdb4);
    switch (cmd) {
    case 0x2e:
        if (*(int *)(g + 0x6bc) == cmd) return;
        func_ov082_020b8a10(this);
        return;
    case 0x2f:
        if (*(int *)(g + 0x6bc) == cmd) return;
        *(int *)(this + 8) = 1;
        func_ov082_020b9210(this);
        return;
    case 0x30:
        *(int *)this = 1;
        if (*(int *)(g + 0x6bc) == cmd) return;
        func_ov082_020b9210(this);
        func_ov082_020b9168(this);
        return;
    }
}
