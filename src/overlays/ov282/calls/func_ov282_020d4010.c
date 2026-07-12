/* Store the owner (param_2) at +4; if a spawn position (param_3) is given, copy it to
 * +0x20 and run the ov107 attach. */
extern void func_ov107_020c5c54(int a, int b);
struct Vec3_020d3ffc { int x, y, z; };
void func_ov282_020d4010(int param_1, int param_2, int param_3) {
    *(int *)(param_1 + 4) = param_2;
    if (param_3 == 0) return;
    *(struct Vec3_020d3ffc *)(param_1 + 0x20) = *(struct Vec3_020d3ffc *)param_3;
    func_ov107_020c5c54(*(int *)param_1, param_1 + 0x20);
}
