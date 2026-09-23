/* Enter move 7 of the ov237 actor: the +0x30 timer clears, the +0x54 flag is set and pose 0x12
 * plays; without a +0x4b4 hold an effect 0xf plays at the +0x38 point, then the brain waits on
 * 020cfb98. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov237_020cfb98(void);

void func_ov237_020cfb10(int *node)
{
    int *state = (int *)node[1];

    state[0xd] = 7;
    state[0xc] = 0;
    *(u8 *)(state + 0x15) = 1;
    func_ov107_020c9264(*state, 0x12, 0);
    if (*(int *)(*state + 0x4b4) == 0) {
        func_ov107_020c0b90(*state, 0xf, *(Vec3 *)state[0xe], 0);
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov237_020cfb98);
}
