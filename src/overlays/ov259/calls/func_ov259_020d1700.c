/* Forward a body sweep of the ov259 actor to its +0x214 rig while it is live (+0x50 == 1). */
typedef struct { int x, y, z; } Vec3;

extern void func_ov259_020d1bf8(int rig, int a, int b, Vec3 lift);

void func_ov259_020d1700(char *self, int a, int b, Vec3 lift)
{
    if (*(int *)(self + 0x50) != 1) {
        return;
    }
    func_ov259_020d1bf8(*(int *)(self + 0x214), a, b, lift);
}
