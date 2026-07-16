/* func_ov025_020918d8 -- scroll the menu list to a target row with easing, ov008.
 * Kicks the low-level scroll (func_ov025_020917e4) then computes the eased pixel delta:
 * a 64-bit multiply of the row span ((p3-p4)*0x10 - 1) * p2 against the remaining distance
 * (p5 - obj+0x2f8), rounded down to whole rows (/16). If a scroll is already committed
 * (obj+8 != 0) it stops; otherwise it applies the delta to the list object (obj+0x70) via
 * func_ov025_02090854. */
extern void func_ov025_020917e4(int obj, int a, int b, int c);
extern long long func_02020400(int a, int b);
extern void func_ov025_02090854(int obj, int listObj, int rows);

void func_ov025_020918d8(int obj, int p2, int p3, int p4, int p5) {
    long long v;
    int iv;
    func_ov025_020917e4(obj, p2, p3, p4);
    v = func_02020400(p2 * ((p3 - p4) * 0x10 - 1), p5 - *(int *)(obj + 0x2f8));
    if (*(int *)(obj + 8) != 0) {
        return;
    }
    iv = (int)v + 8;
    func_ov025_02090854(obj, *(int *)(obj + 0x70),
                        (int)(iv + ((unsigned int)(iv >> 3) >> 0x1c)) >> 4);
}
