/* Slam entry of the ov268 enemy (x3 with ov209/ov268): sends the owner command 3 with the zero
 * vector, fires reaction 0x15f mode 8 at the +0x3c4 part's +4 point, clears the +0x2c timer and
 * the +0x49 byte and hands the tick over to func_ov268_020d273c. */
typedef struct { int x, y, z; } Vec3;

extern void func_ov107_020c0b90(int owner, int mode, Vec3 v, int flag);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02041dc8;
extern void func_ov268_020d273c(int *node);

void func_ov268_020d26bc(int *node)
{
    int *state = (int *)node[1];

    func_ov107_020c0b90(*state, 3, data_02041dc8, 0);
    func_ov107_020c5af8(*state, 0x15f, 8, (void *)(*(int *)(*state + 0x3c4) + 4));
    state[0xb] = 0;
    *(unsigned char *)((char *)state + 0x49) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov268_020d273c);
}
