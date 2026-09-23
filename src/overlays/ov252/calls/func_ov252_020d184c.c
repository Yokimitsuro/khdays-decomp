/* Hover entry of an ov252 part: it is knocked back at the origin (mode 0xc), +0x78 = 28.0, +0x64
 * clears, the +0x88 / +0x89 flags are set and the node moves on to 020d18c0. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov252_020d18c0(void);
extern const Vec3 data_02041dc8;

void func_ov252_020d184c(int *node)
{
    int *state = (int *)node[1];

    func_ov107_020c0b90(*state, 0xc, data_02041dc8, 0);
    state[0x1e] = 0x1c000;
    state[0x19] = 0;
    *((u8 *)state + 0x88) = 1;
    *((u8 *)state + 0x89) = 1;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov252_020d18c0);
}
