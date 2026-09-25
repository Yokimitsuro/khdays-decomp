/* func_ov245_020cfa14 -- hit filter of the +0x214 sub-state while its +0x38 stock is positive:
 * a hit flagged 0x2000 marks the hit consumed (+0x28 = 1), decrements the stock (clamped 0..2)
 * and, unless the hit is the 0x88-flagged 0x80-kind one, fires reaction 0x15a of the kind picked
 * from the 4-entry table data_ov245_020d71a4 by the +0x3c parity (offset 2 when neither 0x22 bit is
 * set) at the state's +8 anchor (020c5af8), toggling the parity; then sub-state 3 when the stock
 * is empty, 5 otherwise. Returns 1 when the stock was positive. */
struct Pair { unsigned char v[2]; };
struct HitWord { unsigned int lo : 16, hi : 16; };
typedef struct Pair Bytes4[2];

extern void func_ov107_020c5af8(int actor, int id, int kind, void *anchor);
extern const struct Pair data_ov245_020d71a4[2];

int func_ov245_020cfa14(int self, int a, unsigned int *hit) {
    int *state = *(int **)(self + 0x214);
    struct Pair table[2];
    table[1] = data_ov245_020d71a4[1];
    table[0] = data_ov245_020d71a4[0];
    int stock;

    if (state[0xe] <= 0) {
        return 0;
    }
    if (((unsigned short)*hit & 0x2000) != 0) {
        stock = hit[10] = 1;    /* the consumed flag is also the one unit taken from the stock */
        stock = state[0xe] - stock;
        state[0xe] = stock;
        if (stock > 2) {
            stock = 2;
        } else if (stock < 0) {
            stock = 0;
        }
        state[0xe] = stock;
        if ((int)hit[10] > 0) {
            if (!((((struct HitWord *)hit)->lo & 8) != 0 && (((struct HitWord *)hit)->lo & 0x80) != 0 && ((struct HitWord *)hit)->hi == 0x80)) {
            if ((((struct HitWord *)hit)->lo & 0x22) != 0) {
                func_ov107_020c5af8(self, 0x15a, table[0].v[*(unsigned char *)(state + 0xf)], (void *)state[2]);
            } else {
                func_ov107_020c5af8(self, 0x15a, table[1].v[*(unsigned char *)(state + 0xf)], (void *)state[2]);
            }
            *(unsigned char *)(state + 0xf) ^= 1;
            }
        }
    }
    *(unsigned char *)(*state + 0x1c7) = state[0xe] == 0 ? 3 : 5;
    return 1;
}
