/* Enter the pounce: play animation 0x18, re-acquire the target and face it, reset the counters,
 * seed the timer at 0x6000, send the canned 4-byte event to the notify hook and hand off.
 *
 * Matched byte-exact 2026-07-23, closing an old park filed as a "2-halfword read-order tie".
 * It is not a tie: bind a pointer to the DESTINATION, copy the HIGH halfword first through it,
 * and pass that same pointer to the callback. That is what makes mwcc read +6 before +4 and
 * reuse the table base register for the second load, as the ROM does; a struct assignment reads
 * the low one first and keeps the base alive.
 *
 * One of three byte-identical siblings. */
struct pt { unsigned short a, b; };
extern void func_ov107_020c9264(int a, int b, int c);
extern int  func_ov107_020cab14(int obj, void *out);
extern void VEC_Subtract(void *a, void *b, void *c);
extern int  func_020050b4(int x, int z);
extern void func_0203c634(int self, int idx, int cb);
extern struct pt data_ov282_020d4700[];
extern void func_ov282_020d3378(void);

void func_ov282_020d32b4(int *self) {
    int *state = (int *)self[1];
    int v[3];
    struct pt pt;
    struct pt *pp;
    void (*fp)(int, void *, int);
    int target;

    func_ov107_020c9264(*state, 0x18, 0);
    target = func_ov107_020cab14(*state, 0);
    state[4] = target;
    if (target != 0) {
        VEC_Subtract((void *)(target + 0x190), (void *)state[1], v);
        state[0xa] = func_020050b4(v[0], v[2]);
    }
    state[0xb] = 0;
    state[0x14] = 0x6000;
    pp = &pt;
    pp->b = data_ov282_020d4700[1].b;
    pp->a = data_ov282_020d4700[1].a;
    fp = *(void (**)(int, void *, int))(*state + 0x24);
    if (fp != 0) {
        fp(*state, pp, 4);
    }
    state[0x18] = 0;
    *(char *)((int)state + 0x66) = 0;
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov282_020d3378);
}
