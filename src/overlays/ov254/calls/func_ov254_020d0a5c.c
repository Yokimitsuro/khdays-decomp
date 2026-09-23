/* Move entry: the actor plays pose 0x13, is knocked back with mode 3 in place, the +0x44 timer and
 * the +0x70 / +0x74 flags clear and the node moves to 020d0ad4. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

extern void func_ov107_020c9264(int actor, int pose, int flag);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02041dc8;
extern void func_ov254_020d0ad4(void);

void func_ov254_020d0a5c(int *node)
{
    int *state = (int *)node[1];

    func_ov107_020c9264(*state, 0x13, 0);
    func_ov107_020c0b90(*state, 3, data_02041dc8, 0);
    state[0x11] = 0;
    *((u8 *)state + 0x70) = 0;
    *((u8 *)state + 0x74) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov254_020d0ad4);
}
