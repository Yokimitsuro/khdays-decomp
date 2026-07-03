extern void func_ov044_020b3b30(void *this);
extern void func_ov044_020b4330(void *this);
extern void func_ov044_020b4288(void *this);

void func_ov044_020b5204(char *this, int cmd) {
    char *g = *(char **)(this + 0xdb4);
    switch (cmd) {
    case 0x2e:
        if (*(int *)(g + 0x6bc) == cmd) return;
        func_ov044_020b3b30(this);
        return;
    case 0x2f:
        if (*(int *)(g + 0x6bc) == cmd) return;
        *(int *)(this + 8) = 1;
        func_ov044_020b4330(this);
        return;
    case 0x30:
        *(int *)this = 1;
        if (*(int *)(g + 0x6bc) == cmd) return;
        func_ov044_020b4330(this);
        func_ov044_020b4288(this);
        return;
    }
}
