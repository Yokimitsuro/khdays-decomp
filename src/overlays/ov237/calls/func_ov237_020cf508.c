/* Enter the charge of the ov237 actor: pose 0xc plays with effects 9 and 10 at the +0x38 point, the
 * +0x30 clock clears, +0x34 = 1, the +0x1c timer clears, the +0x54 / +0x55 flags are set and +0x57
 * cleared, +0x18 takes the +0x14 value, +0x58 clears and the brain waits on 020cf5c0. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov237_020cf5c0(void);

void func_ov237_020cf508(int *node)
{
    int *state = (int *)node[1];

    func_ov107_020c9264(*state, 0xc, 0);
    func_ov107_020c0b90(*state, 9, *(Vec3 *)state[0xe], 0);
    func_ov107_020c0b90(*state, 10, *(Vec3 *)state[0xe], 0);
    state[0xc] = 0;
    state[0xd] = 1;
    state[7] = 0;
    *((u8 *)state + 0x55) = 1;
    *((u8 *)state + 0x54) = 1;
    *((u8 *)state + 0x57) = 0;
    state[6] = state[5];
    state[0x16] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov237_020cf5c0);
}
