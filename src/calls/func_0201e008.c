extern int FS_SeekFile(void *file, int offset, int origin);
extern int OS_UnlockByWord_0x0200ae4c(void *file, void *buf, int size);

int func_0201e008(char *p, void *buf, int size, int rel_off) {
    FS_SeekFile(p + 0x5c, *(int *)(p + 0xa4) + rel_off, 0);
    return OS_UnlockByWord_0x0200ae4c(p + 0x5c, buf, size);
}
