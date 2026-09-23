/* Wait tick of the ov237 actor: once the +4 rig is idle, a free linked partner (+0x4ac set, its
 * +0x4b0 clear) or a pending +0x4a8 request clears the request and ends the move: 020cd8c8 decides
 * (else the next move is 4); otherwise pose 0 plays. */
typedef unsigned char u8;

extern int func_ov237_020cd8c8(int *node);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov107_020c9264(char *a, int b, int c);

void func_ov237_020ce61c(int *node)
{
    int *state = (int *)node[1];
    int free = 0;
    char *actor = (char *)*state;

    if (*(int *)(actor + 0x4ac) != 0 && *(int *)(*(int *)(actor + 0x4a4) + 0x4b0) == 0) {
        free = 1;
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    if (free != 0 || (free == 0 && *(int *)(actor + 0x4a8) != 0)) {
        *(int *)(actor + 0x4a8) = 0;
        if (func_ov237_020cd8c8(node) != 0) {
            func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
            return;
        }
        *(signed char *)(*state + 0x1c7) = 4;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    func_ov107_020c9264(actor, 0, 0);
}
