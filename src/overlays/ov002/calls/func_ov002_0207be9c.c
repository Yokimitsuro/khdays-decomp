/*
 * func_ov002_0207be9c - apply a queued input event to an object (ARM).
 *
 * Dispatches on the event type param_2[0]: type 1 records the button code param_2[4] into
 * param_1+0x2c2 and marks the input state (param_1+0x2c1) as 2; type 2 confirms the current menu
 * selection - if the highlighted index (signed halfword at param_1+0x2c4) is valid it runs
 * func_ov002_02073ed0 on it, then sets the "confirmed" bit at param_1+0x2c3. Other event types are
 * ignored.
 */
extern void func_ov002_02073ed0(int a, int b, int c);

void func_ov002_0207be9c(int param_1, unsigned char *param_2)
{
    switch (param_2[0]) {
    case 1:
        *(unsigned char *)(param_1 + 0x2c2) = param_2[4];
        *(unsigned char *)(param_1 + 0x2c1) = 2;
        break;
    case 2:
        {
            short v = *(short *)(param_1 + 0x2c4);
            if (v >= 0) {
                func_ov002_02073ed0(v, 1, -1);
            }
            *(unsigned char *)(param_1 + 0x2c3) |= 1;
        }
        break;
    }
}
