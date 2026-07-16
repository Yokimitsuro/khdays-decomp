/* func_ov024_0208669c -- MobiClip: get the 8448-byte decoder lookup table, cached in fast memory.
 *
 * This is the template for the four getters at 0208669c / 0208670c / 0208677c / 02086620.
 * Each owns one read-only payload in the overlay's .rodata and one cache slot in the arena
 * descriptor data_ov024_0209bb30 (handed its backing store by func_ov024_020865f8). On the
 * first call the payload is copied into the arena and the carved pointer is remembered in the
 * slot; later calls return it straight back. The point is speed, not mutation -- the tables
 * are const and the decoder indexes them per-pixel, so a copy in fast memory pays for itself.
 * If the arena cannot fit the payload, the .rodata original is returned uncached and the
 * decoder simply runs slower off it; that fallback is why the copy is only ever an optimisation.
 *
 * data_ov024_0208a7c4 is 8448 bytes of u16 entries consumed by the video decoder.
 * Its payload is contiguous with the code blob: 0x0208a7c4 + 0x2100 == 0x0208c8c4. */
extern void MIi_CpuCopyFast(const void *src, void *dest, unsigned int size);
extern int data_ov024_0209bb30[];
extern unsigned char data_ov024_0208a7c4[];

void *func_ov024_0208669c(void) {
    void *p;

    if (data_ov024_0209bb30[1] == 0) {
        if ((unsigned int)data_ov024_0209bb30[3] >= 0x2100) {
            p = (void *)data_ov024_0209bb30[4];
            data_ov024_0209bb30[1] = (int)p;
            MIi_CpuCopyFast(data_ov024_0208a7c4, p, 0x2100);
            data_ov024_0209bb30[4] += 0x2100;
            data_ov024_0209bb30[3] -= 0x2100;
        } else {
            return data_ov024_0208a7c4;
        }
    }
    return (void *)data_ov024_0209bb30[1];
}
