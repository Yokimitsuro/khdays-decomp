/* func_ov000_0204e1dc -- fade the logo palette toward white, ov000.
 * NONMATCHING: register-allocation tie. Three loop pointers (src, dst, end) fit in
 * ip/lr/r4; the retail build parks the invariant `end` in the callee-saved r4 while
 * our mwcc parks `dst` there, shuffling ip/lr/r4. Logic is byte-exact. For the port.
 *
 * For each 15-bit BGR color in the working palette (heap+0x4c6c), lerps every
 * component toward 0x1f by scale/16 into the upload buffer (heap+0x4e6c), then queues
 * the palette DMA (GFXi_EnqueueCommand type 0xf, 0x200 bytes). */
extern void *NNSi_FndGetCurrentRootHeap(void);
extern void GFXi_EnqueueCommand(int type, int a, void *src, int size);
void func_ov000_0204e1dc(int scale) {
    char *h = (char *)NNSi_FndGetCurrentRootHeap();
    unsigned short *src = (unsigned short *)(h + 0x4c6c);
    unsigned short *dst = (unsigned short *)(h + 0x4e6c);
    unsigned short *end = dst;
    while (src < end) {
        unsigned short c = *src++;
        int r = c & 0x1f;
        int g = (c >> 5) & 0x1f;
        int b = (c >> 0xa) & 0x1f;
        int nr = r + (scale * (0x1f - r) >> 4);
        int ng = g + (scale * (0x1f - g) >> 4);
        int nb = b + (scale * (0x1f - b) >> 4);
        *dst++ = nr | (ng << 5) | (nb << 10);
    }
    GFXi_EnqueueCommand(0xf, 0, h + 0x4e6c, 0x200);
}
