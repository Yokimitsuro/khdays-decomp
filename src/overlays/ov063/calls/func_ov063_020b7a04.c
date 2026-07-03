extern void func_ov063_020b6330(void *this);
extern void func_ov063_020b6b30(void *this);
extern void func_ov063_020b6a88(void *this);

void func_ov063_020b7a04(char *this, int cmd) {
    char *g = *(char **)(this + 0xdb4);
    switch (cmd) {
    case 0x2e:
        if (*(int *)(g + 0x6bc) == cmd) return;
        func_ov063_020b6330(this);
        return;
    case 0x2f:
        if (*(int *)(g + 0x6bc) == cmd) return;
        *(int *)(this + 8) = 1;
        func_ov063_020b6b30(this);
        return;
    case 0x30:
        *(int *)this = 1;
        if (*(int *)(g + 0x6bc) == cmd) return;
        func_ov063_020b6b30(this);
        func_ov063_020b6a88(this);
        return;
    }
}
