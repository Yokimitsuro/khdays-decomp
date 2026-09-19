/* Once the low nibble of the actor's +0x420 word reaches 4, the cue at data_ov244_020d3724
 * entry 3 goes through the +0x24 hook and pose request 5 is queued; otherwise, once the +0x30
 * child's byte clears, pose request 2 is queued. Either way the node dispatches null. */
struct Nib420 { int lo : 4; };
extern void func_0203c634(void *obj, int idx, void *value);
extern unsigned short data_ov244_020d3724[];

void func_ov244_020d090c(int *node) {
    int *state = (int *)node[1];
    unsigned short pair[2];
    unsigned short *pp;
    void (*cb)();
    int actor = *state;

    if (((struct Nib420 *)(actor + 0x420))->lo >= 4) {
        pp = pair;
        pp[1] = data_ov244_020d3724[7];
        pp[0] = data_ov244_020d3724[6];
        cb = *(void (**)())(*state + 0x24);
        if (cb != 0) cb(*state, pp, 4);
        *(unsigned char *)(*state + 0x1c7) = 5;
        func_0203c634(node, *(signed char *)(node + 8), 0);
        return;
    }
    if (*(unsigned char *)state[0xc] != 0) return;
    *(unsigned char *)(actor + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)(node + 8), 0);
}
