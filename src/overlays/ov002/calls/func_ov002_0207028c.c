/*
 * func_ov002_0207028c - test whether a target point is within an object's horizontal range (ARM).
 *
 * A negative range (param_1[0x20] sign bit set) is a wildcard that always passes. Otherwise it takes
 * the object position (VecFx32 at param_1+0x2c) and the target param_2, flattens both to the ground
 * plane by zeroing their Y components, and returns whether their distance (func_01ff8e94) is within
 * the range param_1[0x20].
 */
extern int func_01ff8e94(void *a, void *b, int c);
typedef struct { int x, y, z; } VecFx32;

int func_ov002_0207028c(int param_1, void *param_2)
{
    int radius = *(int *)(param_1 + 0x20);
    VecFx32 a, b;
    if (radius & 0x80000000) return 1;
    a = *(VecFx32 *)(param_1 + 0x2c);
    b = *(VecFx32 *)param_2;
    a.y = 0;
    b.y = 0;
    return func_01ff8e94(&a, &b, 0) <= *(int *)(param_1 + 0x20);
}
