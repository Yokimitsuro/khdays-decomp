/* Recursive grab-slot path search of the ov261 enemy (and its byte-identical twin). Marks the
 * slot visited (bit 16 of its +0x18 word), records it in the order buffer at the current depth
 * and, when the slot's two 64-bit id masks (+0x1c for ids below 0x40, +0x24 for ids below
 * 0x80) contain the wanted id, copies the order to the output, stores the depth as the limit
 * and the slot into the actor's +0x3ad, returning the depth. Otherwise (depth below 0x20) it
 * recurses into the up-to-four unvisited neighbours listed at +0x38, unmarks the slot and
 * returns the limit found so far; a depth beyond the limit returns 0.
 * Codegen: compiled with opt_dead_assignments off (push/pop scoped); `i` is declared first and the
 * loop re-reads the depth parameter into `cur` before the end-of-list test, as in the ROM (a plain
 * `depth + 1` argument is hoisted out of the loop and the depth stays cached in a register). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

#pragma push
#pragma opt_dead_assignments off
int func_ov262_020d4130(int *state, u8 slot, u16 *order, u32 id, u8 depth, u16 *out, int *limit)
{
    u8 i;
    int list = *(int *)(*state + 0x3a0);
    u32 *entry = (u32 *)(list + 0x18 + slot * 0x24);
    signed char none;
    signed char next;
    int cur;

    if (depth + 1 > *limit) {
        return 0;
    }
    entry[0] = (entry[0] & ~0xff0000) | ((((entry[0] << 8) >> 24) | 1) << 24) >> 8;
    ((u8 *)order)[depth] = slot;
    if ((id < 0x40 && (*(u64 *)(entry + 1) & (1ULL << id)) != 0) ||
        (id >= 0x40 && id < 0x80 && (*(u64 *)(entry + 3) & (1ULL << (id - 0x40))) != 0)) {
        MI_CpuCopy8(order, out, 0x20);
        *limit = depth + 1;
        *(u8 *)(*state + 0x3ad) = slot;
        return depth + 1;
    }
    if (depth + 1 >= 0x20) {
        entry[0] = (entry[0] & ~0xff0000) | ((((entry[0] << 8) >> 24) & ~1) << 24) >> 8;
        return 0;
    }
    none = -1;
    for (i = 0; i < 4; i++) {
        next = *(signed char *)((char *)entry + 0x20 + i);
        cur = depth;
        if (next == none) {
            break;
        }
        if (((*(u32 *)(list + next * 0x24 + 0x18) << 8) >> 24 & 1) == 0) {
            func_ov262_020d4130(state, (u8)next, order, id, cur + 1, out, limit);
        }
    }
    entry[0] = (entry[0] & ~0xff0000) | ((((entry[0] << 8) >> 24) & ~1) << 24) >> 8;
    return *limit;
}
#pragma pop
