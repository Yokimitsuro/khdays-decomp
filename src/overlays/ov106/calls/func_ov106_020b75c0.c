extern void *data_ov106_020b8b60;
extern void func_ov106_020b75e4(void);

void *func_ov106_020b75c0(void) {
    if ((*(unsigned short *)((char *)data_ov106_020b8b60 + 0x8e44) & 2) != 0) {
        return (void *)func_ov106_020b75e4;
    }
    return 0;
}
