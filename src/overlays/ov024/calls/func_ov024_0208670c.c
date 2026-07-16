/* func_ov024_0208670c -- MobiClip: get the 5-bit saturation table, cached in fast memory.
 * data_ov024_0209352c is 768 read-only bytes, verified entry-for-entry to be
 *     sat[i] = clamp((i - 256) >> 3, 0, 31)
 * i.e. an 8-bit-to-5-bit channel conversion with a 256-entry negative guard band, so the
 * decoder can clamp a signed intermediate into an RGB555 channel with one indexed load.
 * Same lazy-cache shape as func_ov024_0208669c; its carved pointer lives in slot +0. */
extern void MIi_CpuCopyFast(const void *src, void *dest, unsigned int size);
extern int data_ov024_0209bb30[];
extern unsigned char data_ov024_0209352c[];

void *func_ov024_0208670c(void) {
    void *p;

    if (data_ov024_0209bb30[0] == 0) {
        if ((unsigned int)data_ov024_0209bb30[3] >= 0x300) {
            p = (void *)data_ov024_0209bb30[4];
            data_ov024_0209bb30[0] = (int)p;
            MIi_CpuCopyFast(data_ov024_0209352c, p, 0x300);
            data_ov024_0209bb30[4] += 0x300;
            data_ov024_0209bb30[3] -= 0x300;
        } else {
            return data_ov024_0209352c;
        }
    }
    return (void *)data_ov024_0209bb30[0];
}
