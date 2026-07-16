/* func_ov009_0204cb9c -- push the four canned descriptors into the screen's work area.
 *
 * The base is data_ov009_020563e4[1] (the screen context pointer), and the four destinations are
 * 0x9680, 0x968c, 0x9698 and 0x96a4 into it -- a stride of 0xc, so they are four consecutive
 * 12-byte slots.
 *
 * mwcc splits each of those offsets differently (0x1680+0x8000 for the first, 0x28c+0x9400 for
 * the rest) because it picks whatever two immediates happen to be encodable; that is automatic
 * and nothing in the source controls it. */

extern void func_0202ff58(int dst, const void *src);
extern int data_ov009_020563e4[];
extern int data_ov009_02056234;
extern int data_ov009_0205624c;
extern int data_ov009_02056264;
extern int data_ov009_0205627c;

void func_ov009_0204cb9c(void) {
    func_0202ff58(data_ov009_020563e4[1] + 0x9680, &data_ov009_02056234);
    func_0202ff58(data_ov009_020563e4[1] + 0x968c, &data_ov009_0205624c);
    func_0202ff58(data_ov009_020563e4[1] + 0x9698, &data_ov009_02056264);
    func_0202ff58(data_ov009_020563e4[1] + 0x96a4, &data_ov009_0205627c);
}
