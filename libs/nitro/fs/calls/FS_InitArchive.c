/* Zeroes the 0x5c-byte archive descriptor and re-clears its four list pointers. */
extern void MI_CpuFill8(void *p, int v, unsigned int len);

void FS_InitArchive(char *arc) {
    MI_CpuFill8(arc, 0, 0x5c);
    *(int *)(arc + 0x10) = 0;
    *(int *)(arc + 0xc) = 0;
    *(int *)(arc + 0x18) = 0;
    *(int *)(arc + 0x14) = 0;
}
