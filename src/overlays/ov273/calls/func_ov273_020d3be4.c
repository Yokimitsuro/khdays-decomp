/* State entry: sends message data_ov273_020d6aac (4 bytes) to the actor's +0x24 hook when set,
 * clears the +0x69 latch, plays pose 0x19, zeroes the +0x1c timer, the +0x6a byte and the +0x70
 * word, then moves the node to 020d0020. */
struct hpair { unsigned short a, b; };

extern void func_ov107_020c9264(int actor, int pose, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern const struct hpair data_ov273_020d6aac;
extern void func_ov273_020d3c60(void);

void func_ov273_020d3be4(int *node) {
    int *state = (int *)node[1];
    struct hpair msg = data_ov273_020d6aac;
    void (*hook)(int, struct hpair *, int) = *(void (**)(int, struct hpair *, int))(*state + 0x24);

    if (hook != 0) {
        hook(*state, &msg, 4);
    }
    *((unsigned char *)state + 0x69) = 0;
    func_ov107_020c9264(*state, 0x19, 0);
    state[7] = 0;
    *((unsigned char *)state + 0x6a) = 0;
    state[0x1c] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov273_020d3c60);
}
