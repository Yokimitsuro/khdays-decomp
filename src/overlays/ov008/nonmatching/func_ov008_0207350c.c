/* NONMATCHING: semantics correct; the ROM emits a redundant u16 truncation on the command
 * (lsr#16; lsl#16; lsr#16) that mwcc elides because it knows `uint >> 16` already fits in 16
 * bits (84B vs 88B). No C form re-introduces the dead narrowing. */
/* func_ov008_0207350c -- ov008 message handler for class 4: dispatches on the message's high
 * half-word — 1 = select entry (func_ov008_02071618 with the low half-word as tag), 2 = confirm
 * (func_ov008_02071ebc). Anything else is ignored. */
extern int  func_ov008_02050cec(void);
extern void func_ov008_02071618(int obj, unsigned short tag, int arg);
extern void func_ov008_02071ebc(int obj);

void func_ov008_0207350c(unsigned int *param_1, int param_2, unsigned int param_3, unsigned int param_4) {
    int obj = func_ov008_02050cec();
    if (param_2 != 4) {
        return;
    }
    {
        unsigned short cmd = (unsigned short)(*param_1 >> 0x10);
        if (cmd != 1) {
            if (cmd != 2) {
                return;
            }
            func_ov008_02071ebc(obj);
            return;
        }
        func_ov008_02071618(obj, (unsigned short)*param_1, 0);
    }
}
