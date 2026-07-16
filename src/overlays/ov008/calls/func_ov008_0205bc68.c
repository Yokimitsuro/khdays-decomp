/* func_ov008_0205bc68 -- advance the ov008 cursor tween one step, ov008.
 * Samples the three x/y/z interpolators (obj+0x11f4/0x1210/0x122c) into the live cursor
 * (obj+0x18/0x1c/0x20), refreshes the derived shadow/projection (func_ov008_0205bbf0),
 * then flags the cursor object dirty (func_02023cc0 on obj+4). */
extern void func_0203602c(void *interp, int *out);
extern void func_ov008_0205bbf0(int obj);
extern void func_02023cc0(void *node);

void func_ov008_0205bc68(int obj) {
    func_0203602c((void *)(obj + 0x11f4), (int *)(obj + 0x18));
    func_0203602c((void *)(obj + 0x1210), (int *)(obj + 0x1c));
    func_0203602c((void *)(obj + 0x122c), (int *)(obj + 0x20));
    func_ov008_0205bbf0(obj);
    func_02023cc0((void *)(obj + 4));
}
