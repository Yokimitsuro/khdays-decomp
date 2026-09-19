/* func_ov253_020cd638 -- hold tick: once bit 0 of the actor's +0x60 low byte is set the +0x30
 * delay is drawn between the +0x224 and +0x228 bounds, each of the four +0x458 parts whose own
 * bit 0 is clear gets its +0x1cc hook called with 0, as does the +0x460 single; the sub-state
 * takes the +0x1c9 byte and the node slot is released. */
struct hw60 { unsigned short lo : 8; unsigned short hi : 8; };

extern int func_02023eb4(int scale);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov253_020cd638(int *node) {
    int *state = (int *)node[1];
    int lo;
    int span;
    int i;

    if ((((struct hw60 *)(*state + 0x60))->lo & 1) == 0) {
        return;
    }
    lo = *(int *)(*state + 0x224);
    span = *(int *)(*state + 0x228) - lo;
    if (span < 0) {
        span = -span;
    }
    state[0xc] = lo + func_02023eb4(span + 1);
    for (i = 0; i < 4; i++) {
        int part = (*(int **)(*state + 0x458))[i];
        if ((((struct hw60 *)(part + 0x60))->lo & 1) == 0) {
            void (*hook)(int, int) = *(void (**)(int, int))(part + 0x1cc);
            if (hook != 0) {
                hook(part, 0);
            }
        }
    }
    {
        int single = *(int *)(*state + 0x460);
        void (*hook)(int, int) = *(void (**)(int, int))(single + 0x1cc);
        if (hook != 0) {
            hook(single, 0);
        }
    }
    *(signed char *)(*state + 0x1c7) = *(signed char *)(*state + 0x100 + 0xc9);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
