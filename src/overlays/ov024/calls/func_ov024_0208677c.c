/* func_ov024_0208677c -- MobiClip: get the 8-bit clamp table, cached in fast memory.
 * data_ov024_020933ac is 384 read-only bytes, verified entry-for-entry to be
 *     clamp8[i] = clamp(i - 64, 0, 255)
 * i.e. a byte clamp with a 64-entry negative guard band (input range -64..319), the usual
 * way to saturate a signed transform result without branching.
 * Same lazy-cache shape as func_ov024_0208669c; its carved pointer lives in slot +0x20. */
extern void MIi_CpuCopyFast(const void *src, void *dest, unsigned int size);
extern int data_ov024_0209bb30[];
extern unsigned char data_ov024_020933ac[];

void *func_ov024_0208677c(void) {
    void *p;

    if (data_ov024_0209bb30[8] == 0) {
        if ((unsigned int)data_ov024_0209bb30[3] >= 0x180) {
            p = (void *)data_ov024_0209bb30[4];
            data_ov024_0209bb30[8] = (int)p;
            MIi_CpuCopyFast(data_ov024_020933ac, p, 0x180);
            data_ov024_0209bb30[4] += 0x180;
            data_ov024_0209bb30[3] -= 0x180;
        } else {
            return data_ov024_020933ac;
        }
    }
    return (void *)data_ov024_0209bb30[8];
}
