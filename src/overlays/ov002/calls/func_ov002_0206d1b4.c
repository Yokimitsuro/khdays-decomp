/*
 * func_ov002_0206d1b4 - look up a record and forward two of its fields to a handler (ARM).
 *
 * Resolves param_2 to a record via func_ov002_0206d194, then calls func_ov002_02077b64 with the
 * record's signed halfword at +0x42 and unsigned halfword at +0x40 in place of param_2, keeping the
 * other arguments (param_1, param_3, param_4, and the byte args param_5/param_6) unchanged.
 */
extern int func_ov002_0206d194(int a);
extern void func_ov002_02077b64(int a, int b, int c, int d, int e, int f, int g);

void func_ov002_0206d1b4(int param_1, int param_2, int param_3, int param_4,
                         signed char param_5, unsigned char param_6)
{
    int result = func_ov002_0206d194(param_2);
    func_ov002_02077b64(param_1, *(short *)(result + 0x42), *(unsigned short *)(result + 0x40),
                        param_3, param_4, param_5, param_6);
}
