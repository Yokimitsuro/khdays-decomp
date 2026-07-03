extern void func_ov030_020b3efc(void *this);
extern void func_ov030_020b46fc(void *this);
extern void func_ov030_020b4654(void *this);

void func_ov030_020b55d0(char *this, int cmd) {
    char *g = *(char **)(this + 0xdb4);
    switch (cmd) {
    case 0x2e:
        if (*(int *)(g + 0x6bc) == cmd) return;
        func_ov030_020b3efc(this);
        return;
    case 0x2f:
        if (*(int *)(g + 0x6bc) == cmd) return;
        *(int *)(this + 8) = 1;
        func_ov030_020b46fc(this);
        return;
    case 0x30:
        *(int *)this = 1;
        if (*(int *)(g + 0x6bc) == cmd) return;
        func_ov030_020b46fc(this);
        func_ov030_020b4654(this);
        return;
    }
}
