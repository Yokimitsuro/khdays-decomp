/* Count-down: starting from the per-id counter at base[id+0x810], scan three 0x28-entry id tables
 * (one per 0x50-byte bank, at bank+0xee0) and decrement the counter once for every table entry
 * equal to id while it is still positive. Returns the remaining count (0 for a negative id).
 *
 * NON-MATCHING (equivalent). Semantics, the predicated u8 decrement (subne/andne), and the loop
 * bounds are right, and with a per-bank table pointer the size matches (116). Residue is a
 * strength-reduction / CSE heuristic (same class as func_ov008_02054d3c): the ROM keeps the inner
 * counter j in [0,0x28) and recomputes base + j*2 + 0xee0 inline each iteration (add rX,base,j
 * lsl#1; +0xe00; ldrh +0xe0), holding only base; mwcc 139 either induces a separate j*2 counter
 * (raw offset spelling, 124 bytes) or hoists a held table pointer (array spelling, 116 bytes but a
 * second callee-saved register and a different addressing/register allocation throughout). No
 * spelling reproduces the recompute-from-base form under our flags. */
typedef unsigned char u8;
typedef unsigned short u16;
extern u8 *data_0204be18;

int func_ov008_0208b148(int id) {
    u8 *base;
    u8 count;
    int i;
    if (id < 0) {
        return 0;
    }
    base = data_0204be18;
    count = base[id + 0x810];
    i = 0;
    do {
        int j = 0;
        do {
            if (id == *(u16 *)(base + j * 2 + 0xee0) && count != 0) {
                count = count - 1;
            }
            j++;
        } while (j < 0x28);
        i++;
        base += 0x50;
    } while (i < 3);
    return count;
}
