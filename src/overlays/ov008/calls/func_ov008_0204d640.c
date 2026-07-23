/* func_ov008_0204d640 -- look up a per-entry status byte: fill a scratch record via
 * func_ov008_0207b960, and when its byte [5] comes back 0, derive it from bit 1 of the entry's
 * flag byte (data_ov008_02090f00's entries[param_1] at +0x2e, stride 6): 0x13 when set, 0
 * otherwise. Returns the signed byte.
 *
 * The park called the residue a "branch-vs-predicate heuristic that build 139 always loses": mwcc
 * predicates a two-store if/else with constant arms (moveq/strbeq/movne/strbne) where the ROM
 * branches (bne else; mov; strb; b end; else: mov; strb) -- exactly 8 bytes, two instructions.
 * A `switch` with an explicit `default` forces the branch form; the same if/else written with the
 * arms swapped still predicates, so it is the `switch` that does it, not the block order.
 * This is the documented "if the ROM branches to out-of-line arms, reach for switch" rule, and it
 * applies to a two-arm select and not only to the three-way ones it was first written for. */
typedef unsigned char u8;
extern void func_ov008_0207b960(int param_1, void *out);

struct Entry {
    u8 a;
    u8 b;
    u8 f2_b0 : 1;
    u8 f2_b1 : 1;
    u8 f2_rest : 6;
    u8 c, d, e;
};
struct Ov008Host {
    char pad[0x2e];
    struct Entry entries[1];
};
extern struct Ov008Host *data_ov008_02090f00;

int func_ov008_0204d640(int param_1) {
    u8 buf[8];
    struct Entry *e = &data_ov008_02090f00->entries[param_1];

    func_ov008_0207b960(param_1, buf);
    if (buf[5] == 0) {
        switch (e->f2_b1) {
        case 1:
            buf[5] = 0x13;
            break;
        default:
            buf[5] = 0;
            break;
        }
    }
    return (signed char)buf[5];
}
