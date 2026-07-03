extern void func_ov099_020bb0d0(void *this);
extern void func_ov099_020bb8d0(void *this);
extern void func_ov099_020bb828(void *this);

void func_ov099_020bc7a4(char *this, int cmd) {
    char *g = *(char **)(this + 0xdb4);
    switch (cmd) {
    case 0x2e:
        if (*(int *)(g + 0x6bc) == cmd) return;
        func_ov099_020bb0d0(this);
        return;
    case 0x2f:
        if (*(int *)(g + 0x6bc) == cmd) return;
        *(int *)(this + 8) = 1;
        func_ov099_020bb8d0(this);
        return;
    case 0x30:
        *(int *)this = 1;
        if (*(int *)(g + 0x6bc) == cmd) return;
        func_ov099_020bb8d0(this);
        func_ov099_020bb828(this);
        return;
    }
}
