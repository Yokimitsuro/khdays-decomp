/* Descend entry of an ov252 part: +0x6c clears, +0x89 = 5, +0x88 = 1, the owner plays effects 0xe and
 * 0xf at the origin and the node moves on to 020d2848. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov252_020d2848(void);
extern const Vec3 data_02041dc8;

void func_ov252_020d27a8(int *node)
{
    int *state = (int *)node[1];
    Vec3 at;

    state[0x1b] = 0;
    *((u8 *)state + 0x89) = 5;
    *((u8 *)state + 0x88) = 1;
    at = data_02041dc8;
    func_ov107_020c0b90(*state, 0xe, at, 0);
    func_ov107_020c0b90(*state, 0xf, at, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov252_020d2848);
}
