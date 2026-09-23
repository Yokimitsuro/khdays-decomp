/* Idle decision of the ov252 actor: once the partner holds no queued move, with the +0xac guard up the
 * next move is 0xe; a pending +0xa8 turn gives 0xd (2 while +0x78 is clear), a pending +0xa4 retreat
 * gives 2; otherwise the +0x5c rest restarts and the node ends when the actor picks a move (020cdef4). */
extern void func_0203c634(int *node, int slot, void *cb);
extern int func_ov252_020cdef4(int *node);

void func_ov252_020d0220(int *node)
{
    int *state = (int *)node[1];

    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    if (state[0x2b] != 0) {
        *(unsigned char *)(*state + 0x1c7) = 0xe;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (state[0x2a] != 0) {
        state[0x2a] = 0;
        if (state[0x1e] == 0) {
            *(unsigned char *)(*state + 0x1c7) = 2;
        } else {
            *(unsigned char *)(*state + 0x1c7) = 0xd;
        }
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (state[0x29] != 0) {
        state[0x29] = 0;
        *(unsigned char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    state[0x17] = 0;
    if (func_ov252_020cdef4(node) != 0) {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
    }
}
