/* Phase switch of the ov125 enemy's sub-node: the +0x34 word holds the current phase (low
 * signed nibble) and the pending one (next nibble). In phases 1/2 an owner +0x1ac bit 1 hit
 * cancels the pending phase, and any +0x1c4 0xa flag cancels it outside phase 0. When a phase
 * is pending it becomes current and its slot-1 handler is installed (0: ce84c, 1: ce8b4,
 * 2: cf1a8), after which the pending nibble is reset to -1. */
struct Phase { int cur : 4, next : 4; };

extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov125_020ce84c(void);
extern void func_ov125_020ce8b4(void);
extern void func_ov125_020cf1a8(void);

void func_ov125_020ce75c(int *node) {
    int *state = (int *)node[1];
    struct Phase *p = (struct Phase *)(state + 0xd);

    if (p->cur == 1 || p->cur == 2) {
        if ((*(unsigned short *)(*state + 0x1ac) & 2) != 0) {
            p->next = 0;
        }
    }
    if ((*(unsigned char *)(*state + 0x1c4) & 0xa) != 0) {
        if (p->cur != 0) {
            p->next = 0;
        }
    }
    if (p->next == -1) {
        return;
    }
    p->cur = p->next;
    switch (p->cur) {
    case 0:
        func_0203c634(node, 1, func_ov125_020ce84c);
        break;
    case 1:
        func_0203c634(node, 1, func_ov125_020ce8b4);
        break;
    case 2:
        func_0203c634(node, 1, func_ov125_020cf1a8);
        break;
    }
    p->next = -1;
}
