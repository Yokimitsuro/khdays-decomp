/* Look up a per-entry status byte: fill a scratch record via func_ov008_0207b960, and when its
 * byte [5] comes back 0, derive it from bit 1 of the entry's flag byte (data_ov008_02090f00's
 * entries[param_1].flags at +0x30): 0x13 when set, 0 otherwise. Returns the signed byte.
 *
 * NON-MATCHING (equivalent). The pointer arithmetic (add base +0x2e, then mla stride 6), the
 * bit-1 extraction (lsl #30; lsr #31; cmp #1) via the bitfield, and everything up to the final
 * assignment reproduce byte-exact. The only residue is a branch-vs-predicate heuristic: mwcc 139
 * predicates the `x=0x13 / x=0` if/else (moveq/strbeq/movne/strbne) where the ROM branches
 * (bne else; mov; strb; b end). Tried `== 1`, bare truth test, and both block orders; build 139
 * always predicates a two-store if/else with constant values. */
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
        if (e->f2_b1 == 1) {
            buf[5] = 0x13;
        } else {
            buf[5] = 0;
        }
    }
    return (signed char)buf[5];
}
