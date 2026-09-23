/* Charge-repeat tick of the ov237 actor: the charge release check runs (020cf2b0); each time the
 * +4 rig finishes, a remaining charge step (+0x34) replays the charge sound (0x12d variant 10) with
 * pose 0x17 and effect 0xb, and the last one clears the +0x30 clock, plays pose 0x18 with effect 0xc
 * (both effects skipped in +0x49e mode 3) and waits on 020cf784. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

extern void func_ov237_020cf2b0(int *node);
extern void func_ov107_020c5af8(int actor, int bank, int variant, int at);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov237_020cf784(void);

void func_ov237_020cf674(int *node)
{
    int *state = (int *)node[1];

    func_ov237_020cf2b0(node);
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    if (state[0xd] == 0) {
        state[0xc] = 0;
        func_ov107_020c9264(*state, 0x18, 0);
        if (*(u8 *)(*state + 0x49e) != 3) {
            func_ov107_020c0b90(*state, 0xc, *(Vec3 *)state[0xe], 0);
        }
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov237_020cf784);
        return;
    }
    state[0xd]--;
    func_ov107_020c5af8(*state, 0x12d, 10, state[0xe]);
    func_ov107_020c9264(*state, 0x17, 0);
    if (*(u8 *)(*state + 0x49e) == 3) {
        return;
    }
    func_ov107_020c0b90(*state, 0xb, *(Vec3 *)state[0xe], 0);
}
