/* Pounce entry of the ov119 enemy (x3 with ov272/ov279): effect 0 spawns at the +0x4c point,
 * reaction 0x121 mode 5 fires there, bit 0 of the +0x388 part's flag byte is raised and bit 1 of
 * the +0x60 high byte cleared; the +0x1c facing aims from the point at the +8 target's +0x74 and
 * is committed to +0xc, the +0x50 timer restarts and the tick hands over to func_ov119_020ce9a8. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int w[4]; } Quat;
typedef struct { unsigned int lo : 8, rest : 24; } Byte8;
struct hw60 { unsigned short lo : 8, hi : 8; };

extern void func_ov107_020c0b90(int actor, int a, Vec3 v, int b);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_0203cd7c(int *dst, const Vec3 *a, const Vec3 *b, const void *c);
extern void func_0202ea48(void *dst, const int *src);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02042264;
extern void func_ov119_020ce9a8(int *node);

void func_ov119_020ce8a8(int *node)
{
    int *state = (int *)node[1];
    int mtx[9];

    func_ov107_020c0b90(*state, 0, *(Vec3 *)state[0x13], 0);
    func_ov107_020c5af8(*state, 0x121, 5, (void *)state[0x13]);
    ((Byte8 *)(*(int *)(*state + 0x388) + 8))->lo |= 1;
    ((struct hw60 *)(*state + 0x60))->hi &= ~2;
    func_0203cd7c(mtx, (Vec3 *)(state[2] + 0x74), (Vec3 *)state[0x13], &data_02042264);
    func_0202ea48(state + 7, mtx);
    *(Quat *)(state + 3) = *(Quat *)(state + 7);
    state[0x14] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov119_020ce9a8);
}
