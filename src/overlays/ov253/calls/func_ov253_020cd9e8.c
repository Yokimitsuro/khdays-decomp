/* func_ov253_020cd9e8 -- recover entry: sends message data_ov253_020d48fc (kind 4) to the
 * actor's +0x24 hook when set, restores pose 1, clears the +0x1c timer and the +0x38 flag and
 * moves the node to 020cda5c. */
struct hpair { unsigned short a, b; };

extern void func_ov107_020c9264(int actor, int pose, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern const struct hpair data_ov253_020d48fc;
extern void func_ov253_020cda5c(void);

void func_ov253_020cd9e8(int *node) {
    int *state = (int *)node[1];
    struct hpair msg = data_ov253_020d48fc;
    void (*hook)(int, struct hpair *, int) = *(void (**)(int, struct hpair *, int))(*state + 0x24);

    if (hook != 0) {
        hook(*state, &msg, 4);
    }
    func_ov107_020c9264(*state, 1, 0);
    state[7] = 0;
    *((unsigned char *)state + 0x38) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov253_020cda5c);
}
