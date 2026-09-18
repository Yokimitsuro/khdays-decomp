/* Summon tick of the ov151 enemy (and its byte-identical twin): the +0x30 timer accumulates the
 * frame-time; from 0x999 the first of the three +0x3c8 items whose +0x60 low bit is clear is
 * launched (cc954) from the +0x394 item's +0x14 point towards the actor's +0xa0 placement, the
 * +0x38 count grows and the state hands off to cea90. */
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_ov152_020d41d4(int item, void *from, void *placement);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov152_020d6310(void);

void func_ov152_020d6274(int *node)
{
    int *state = (int *)node[1];
    int i;

    state[0xc] += *(int *)(*node + 0x2c);
    if (state[0xc] < 0x999) {
        return;
    }
    for (i = 0; i < 3; i++) {
        if ((((struct hw60 *)((*(int **)(*state + 0x3c8))[i] + 0x60))->lo & 1) == 0) {
            func_ov152_020d41d4((*(int **)(*state + 0x3c8))[i], (void *)(*(int *)(*state + 0x394) + 0x14), (void *)(*state + 0xa0));
            state[0xe]++;
            break;
        }
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov152_020d6310);
}
