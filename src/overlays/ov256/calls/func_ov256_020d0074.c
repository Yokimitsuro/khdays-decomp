/* Fall tick of an ov256 part: the +0x10 velocity is the +0x450 owner's +0x2c vector turned by its
 * heading (020cd054); once the partner holds no queued move and it has landed (+0x17a bit 0) +0x4c
 * clears, pose 0x1b plays, it is knocked back at the +0xc point (mode 9), the +0x450 part takes motion
 * 0xc and the node moves on to 020d0144. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
struct Flag17a { u8 b0 : 1; };

extern void func_ov256_020cd054(int *out, int param_2, int *vec);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern int func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov256_020d0144(void);

void func_ov256_020d0074(int *node)
{
    int *state = (int *)node[1];
    Vec3 v;

    func_ov256_020cd054((int *)&v, (int)node, (int *)(*(int *)(*state + 0x450) + 0x2c));
    *(Vec3 *)(state + 4) = v;
    if (*(u8 *)(state[1] + 0xad) == 0) {
        if (!((struct Flag17a *)(*state + 0x17a))->b0) {
            return;
        }
        state[0x13] = 0;
        func_ov107_020c9264(*state, 0x1b, 0);
        func_ov107_020c0b90(*state, 9, *(Vec3 *)state[3], 0);
        func_ov107_020c9ee8(*(int *)(*state + 0x450), 0xc, 0);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov256_020d0144);
        return;
    }
}
