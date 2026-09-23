/* Landing check of the ov259 actor: the +0x14 velocity stops and, once grounded or against a wall
 * (+0x17a bits 0 / 1), it turns to the +8 target (+0x78 / +0x7c heading) and the next move is 0xa. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
struct Flag17a { u8 b0 : 1; u8 b1 : 1; };

extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_020050b4(int x, int y);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02041dc8;

void func_ov259_020cf474(int *node)
{
    int *state = (int *)node[1];
    Vec3 d;

    *(Vec3 *)(state + 5) = data_02041dc8;
    if (!((struct Flag17a *)(*state + 0x17a))->b0 && !((struct Flag17a *)(*state + 0x17a))->b1) {
        return;
    }
    VEC_Subtract((Vec3 *)(state[2] + 0x190), (Vec3 *)(*state + 0xb0), &d);
    state[0x1e] = state[0x1f] = func_020050b4(d.x, d.z);
    *(signed char *)(*state + 0x1c7) = 0xa;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
