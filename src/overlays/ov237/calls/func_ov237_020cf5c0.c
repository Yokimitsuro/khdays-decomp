/* Charge tick of the ov237 actor: the +0x30 clock runs up at the frame rate and past 1.99 the charge
 * releases (020cf2b0); once the +4 rig is idle the charge sound (0x12d variant 10) plays at the +0x38
 * point with pose 0x17 and effect 0xb, and the brain waits on 020cf674. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

extern void func_ov237_020cf2b0(int *node);
extern void func_ov107_020c5af8(int actor, int bank, int variant, int at);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov237_020cf674(void);

void func_ov237_020cf5c0(int *node)
{
    int *state = (int *)node[1];

    state[0xc] += *(int *)(node[0] + 0x2c);
    if (state[0xc] >= 0x1fe0) {
        func_ov237_020cf2b0(node);
    }
    if (*(u8 *)(state[1] + 0xad) == 0) {
        func_ov107_020c5af8(*state, 0x12d, 10, state[0xe]);
        func_ov107_020c9264(*state, 0x17, 0);
        func_ov107_020c0b90(*state, 0xb, *(Vec3 *)state[0xe], 0);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov237_020cf674);
        return;
    }
}
