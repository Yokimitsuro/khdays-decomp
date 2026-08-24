typedef unsigned int u32;

extern u32 func_020235d0(u32 field, int width);
extern void func_020235e8(u32 field, int width, u32 value);

void func_ov004_0204f9cc(void) {
    int i;
    u32 field;
    int enabled;

    if (func_020235d0(0x1913, 2) != 0) {
        return;
    }

    field = 0x28e7;
    for (i = 1; i <= 0x5d; i++, field += 3) {
        enabled = func_020235d0(field, 3) == 3;
        if (enabled == 0) {
            return;
        }
    }

    func_020235e8(0x1913, 2, 1);
}
