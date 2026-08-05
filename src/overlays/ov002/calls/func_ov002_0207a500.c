/*
 * func_ov002_0207a500 - record a move delta and apply it (ARM).
 *
 * Snapshots the object's current position (the Vec3 at param_1+0xd0) and stores the delta from the
 * requested target position param_2 into param_1's pending-move fields (+0x1a4/+0x1a8/+0x1ac). Then
 * hands the target off to func_0202b450 against the object's transform block at param_1+0x28.
 */
extern void func_0202b450(int a, int b);
typedef struct { int x, y, z; } Vec3;

void func_ov002_0207a500(int param_1, int *param_2)
{
    Vec3 tmp = *(Vec3 *)(param_1 + 0xd0);
    *(int *)(param_1 + 0x1a4) = param_2[0] - tmp.x;
    *(int *)(param_1 + 0x1a8) = param_2[1] - tmp.y;
    *(int *)(param_1 + 0x1ac) = param_2[2] - tmp.z;
    func_0202b450(param_1 + 0x28, (int)param_2);
}
