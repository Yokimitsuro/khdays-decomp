/* func_ov025_0209e820 -- query (and optionally set) item param_1's two flags.
 * When param_2 is set, marks it in the "owned" set (ctx+0x238) first. Returns bit0 = owned,
 * bit1 = present in the second set (ctx+0x248). */
extern int  func_ov025_02084afc(void);
extern void func_02025640(int set, unsigned int bit);
extern int  func_02025694(int set, unsigned int bit);

unsigned int func_ov025_0209e820(unsigned int param_1, unsigned int param_2) {
    int ctx = func_ov025_02084afc();
    if (param_2 != 0) {
        func_02025640(ctx + 0x238, param_1);
    }
    param_2 = (func_02025694(ctx + 0x238, param_1) != 0);
    return param_2 | (unsigned int)(func_02025694(ctx + 0x248, param_1) != 0) << 1;
}
