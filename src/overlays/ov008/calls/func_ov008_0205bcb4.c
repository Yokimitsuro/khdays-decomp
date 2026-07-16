/* func_ov008_0205bcb4 -- start the ov008 menu cursor tween toward a slot, ov008.
 * Kicks off three 1-D interpolators (mode 2) for x/y/z from the live cursor (obj+0x18/0x1c/0x20)
 * to the slot's target (rect[0/1/2]) over `dur`, arms each (func_02035ffc), then refreshes the
 * derived shadow/offset positions (func_ov008_0205bc68). */
extern void func_02035fb0(int *interp, int mode, unsigned int from, unsigned int to, unsigned int dur);
extern void func_02035ffc(int *interp);
extern void func_ov008_0205bc68(int obj);

void func_ov008_0205bcb4(int obj, unsigned int *rect, unsigned int dur) {
    func_02035fb0((int *)(obj + 0x11f4), 2, *(unsigned int *)(obj + 0x18), rect[0], dur);
    func_02035fb0((int *)(obj + 0x1210), 2, *(unsigned int *)(obj + 0x1c), rect[1], dur);
    func_02035fb0((int *)(obj + 0x122c), 2, *(unsigned int *)(obj + 0x20), rect[2], dur);
    func_02035ffc((int *)(obj + 0x11f4));
    func_02035ffc((int *)(obj + 0x1210));
    func_02035ffc((int *)(obj + 0x122c));
    func_ov008_0205bc68(obj);
}
