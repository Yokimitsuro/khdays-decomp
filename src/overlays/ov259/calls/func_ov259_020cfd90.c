/* Guard tick of the ov259 actor: the +0x68 timer accumulates the frame rate and the aim refreshes
 * (020cdcac). While guarding (+0x44) bits 0-1 of +0x1ae are set; otherwise past the +0x64 limit
 * pose 7 plays and the node moves on to 020cfe0c. */
typedef unsigned short u16;

extern void func_ov259_020cdcac(int *node);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov259_020cfe0c(void);

void func_ov259_020cfd90(int *node)
{
    int *state = (int *)node[1];

    state[0x1a] += *(int *)(node[0] + 0x2c);
    func_ov259_020cdcac(node);
    if (state[0x11] != 0) {
        *(u16 *)(*state + 0x100 + 0xae) |= 3;
        return;
    }
    if (state[0x1a] <= state[0x19]) {
        return;
    }
    func_ov107_020c9264(*state, 7, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov259_020cfe0c);
}
