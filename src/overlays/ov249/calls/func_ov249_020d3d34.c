/* Placement setter of the ov249 actor: its position is set (020c5c54) to the given point raised by the
 * +0x70 height, the +0x398 goal to the second point, and bit 0 of the +0x60 high byte is raised. */
typedef struct { int x, y, z; } Vec3;

extern void func_ov107_020c5c54(int owner, Vec3 *v);

void func_ov249_020d3d34(int self, Vec3 pos, Vec3 goal)
{
    Vec3 at = pos;

    at.y += *(int *)(self + 0x70);
    func_ov107_020c5c54(self, &at);
    *(Vec3 *)(self + 0x398) = goal;
    {
        unsigned short hv = *(unsigned short *)(self + 0x60);

        *(unsigned short *)(self + 0x60) =
            (unsigned short)((hv & ~0xff00) | (((((unsigned int)hv << 0x10) >> 0x18 | 1) << 0x18) >> 0x10));
    }
}
