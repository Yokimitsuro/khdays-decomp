/* Knock the actor back in place (mode 2) at its feet (x/z of +0xb0, height +0x4d4) and fire
 * reaction 0x16d there, mode 0x11 for a non-negative side and 0x10 otherwise. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;

extern void func_ov107_020c0b90(char *owner, int mode, Vec3 at, int flag);
extern void func_ov107_020c5af8(char *owner, int id, u16 mode, void *at);

void func_ov254_020cdbbc(char *self, int side)
{
    Vec3 at;
    int z = *(int *)(self + 0xb8);
    int y = *(int *)(self + 0x4d4);
    int x = *(int *)(self + 0xb0);

    at.x = x;
    at.y = y;
    at.z = z;
    func_ov107_020c0b90(self, 2, at, 0);
    func_ov107_020c5af8(self, 0x16d, side >= 0 ? 0x11 : 0x10, &at);
}
