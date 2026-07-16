/* func_ov025_0208e434 -- move the menu highlight to a slot (0..0xb), ov008.
 * Clamps the requested slot into [0, 0xb]. On the first move (prev slot obj+0x11f0 < 0) it
 * snaps the highlight box straight to the slot rect (MI_CpuCopy8 of obj+0x70+slot*0x40 into
 * obj+0x18) and shows it (func_ov025_0208e184); afterwards it animates toward the slot
 * (func_ov025_0208e248). Records the slot as the new previous. */
extern void func_ov025_0208e248(int obj, unsigned int *rect, unsigned int mode);
extern void MI_CpuCopy8(unsigned short *src, unsigned short *dst, int size);
extern void func_ov025_0208e184(int obj);

void func_ov025_0208e434(int obj, int slot, unsigned int mode) {
    if (slot < 0) {
        slot = 0;
    }
    if (slot >= 0xc) {
        slot = 0xb;
    }
    if (*(int *)(obj + 0x11f0) >= 0) {
        func_ov025_0208e248(obj, (unsigned int *)(obj + 0x70 + slot * 0x40), mode);
    } else {
        MI_CpuCopy8((unsigned short *)(obj + 0x70 + slot * 0x40), (unsigned short *)(obj + 0x18), 0xc);
        func_ov025_0208e184(obj);
    }
    *(int *)(obj + 0x11f0) = slot;
}
