/* func_ov024_02086620 -- MobiClip: get the 0x659c-byte video decoder code blob, cached in fast memory.
 * Same lazy-cache shape as func_ov024_0208669c, but it draws on the second arena (+0x14/+0x18,
 * set up by func_ov024_020865d8) rather than the data arena, because the payload at
 * data_ov024_0208c8c4 is position-independent CODE: once copied it is entered through the
 * decoder context's function pointer. func_ov024_020865c4 returns the same 0x659c length.
 * If the arena cannot hold it, the overlay's own copy is used in place. */
extern void MIi_CpuCopyFast(const void *src, void *dest, unsigned int size);
extern int data_ov024_0209bb30[];
extern unsigned char data_ov024_0208c8c4[];

void *func_ov024_02086620(void) {
    void *p;

    if (data_ov024_0209bb30[2] == 0) {
        if ((unsigned int)data_ov024_0209bb30[5] >= 0x659c) {
            p = (void *)data_ov024_0209bb30[6];
            data_ov024_0209bb30[2] = (int)p;
            MIi_CpuCopyFast(data_ov024_0208c8c4, p, 0x659c);
            data_ov024_0209bb30[6] += 0x659c;
            data_ov024_0209bb30[5] -= 0x659c;
        } else {
            return data_ov024_0208c8c4;
        }
    }
    return (void *)data_ov024_0209bb30[2];
}
