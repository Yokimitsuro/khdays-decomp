extern void MI_CpuFill8(void *dst, int val, int size);
/* Zero the 0x10-byte block at obj+0x44 and clear obj+0x3c / obj+0x40. */
void func_ov015_02080684(int obj) {
    MI_CpuFill8((void *)(obj + 0x44), 0, 0x10);
    *(int *)(obj + 0x3c) = 0;
    *(unsigned char *)(obj + 0x40) = 0;
}
