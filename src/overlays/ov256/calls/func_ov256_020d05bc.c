/* Hit reaction of an ov256 helper: its owner's +0x398 part is knocked back at the +8 point (mode 4),
 * the owner's next move clears and the hit is taken (1). */
typedef struct { int x, y, z; } Vec3;

extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);

int func_ov256_020d05bc(char *self)
{
    int *state = *(int **)(self + 0x214);

    func_ov107_020c0b90(*(int *)(*state + 0x398), 4, *(Vec3 *)state[2], 0);
    *(signed char *)(*state + 0x1c7) = 0;
    return 1;
}
