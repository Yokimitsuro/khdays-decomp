/*
 * func_ov002_02053634 - forwarding thunk that prepends a context pointer (ARM).
 *
 * Calls func_ov002_0205499c with the subsystem context (data_ov002_0207f60c's base + 0xdc) as the
 * first argument, followed by this function's seven arguments unchanged. Arguments 5 and 6 are a
 * byte and a halfword; the rest are words. The four stack arguments (param_4..param_7) are marshalled
 * into the callee's outgoing stack frame.
 */
extern int data_ov002_0207f60c;
extern void func_ov002_0205499c(int a, int b, int c, int d, int e, int f, int g, int h);

void func_ov002_02053634(int param_1, int param_2, int param_3, int param_4,
                         unsigned char param_5, unsigned short param_6, int param_7)
{
    int base = *(int *)&data_ov002_0207f60c;
    func_ov002_0205499c(base + 0xdc, param_1, param_2, param_3, param_4, param_5, param_6, param_7);
}
