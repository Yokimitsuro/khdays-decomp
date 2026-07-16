/* func_ov025_02082c80 -- push the four canned descriptors into the screen's work area.
 *
 * The base is data_ov025_020b5744[1] (the screen context pointer), and the four destinations are
 * 0x9680, 0x968c, 0x9698 and 0x96a4 into it -- a stride of 0xc, so they are four consecutive
 * 12-byte slots.
 *
 * mwcc splits each of those offsets differently (0x1680+0x8000 for the first, 0x28c+0x9400 for
 * the rest) because it picks whatever two immediates happen to be encodable; that is automatic
 * and nothing in the source controls it. */

extern void func_0202ff58(int dst, const void *src);
extern int data_ov025_020b5744[];
extern int data_ov025_020b49d8;
extern int data_ov025_020b49f0;
extern int data_ov025_020b4a08;
extern int data_ov025_020b4a20;

void func_ov025_02082c80(void) {
    func_0202ff58(data_ov025_020b5744[1] + 0x9680, &data_ov025_020b49d8);
    func_0202ff58(data_ov025_020b5744[1] + 0x968c, &data_ov025_020b49f0);
    func_0202ff58(data_ov025_020b5744[1] + 0x9698, &data_ov025_020b4a08);
    func_0202ff58(data_ov025_020b5744[1] + 0x96a4, &data_ov025_020b4a20);
}
