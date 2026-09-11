/* NONMATCHING: 90B vs 100B. Everything now matches byte-for-byte except one
 * optimization tie. The ROM re-reads `index` from its stack home and recomputes
 * index*2 / index*2+1 fresh at each of the two P2_ExtractString calls, so it
 * needs only three callee-saved registers (push {r3,r4,r5,r6,lr} + sub sp,#4).
 * mwcc 3.0/139 at -O4,p instead promotes the common index<<1 into a fourth
 * callee-saved register (r7) before the first call and reuses it (+1) for the
 * second, which folds the outgoing-arg slot into the push list and drops the
 * ldr+lsls pair and both `add sp,#4`. That is the whole remaining -10 bytes.
 *
 * No C form un-caches it: index*2, index<<1, index+index, 1+index*2,
 * index+index+1, per-call scoped locals, a single reused local, and a named
 * result local for each call all produce byte-identical output. mwcc normalises
 * every spelling to the same value before CSE, so the lever is not the
 * expression tree; it is the allocator's partial-redundancy heuristic, which
 * here has a free register and takes it.
 *
 * Two things that ARE fixed relative to the previous candidate and should be
 * kept: the flag test is `rec[0] >= 0` with the fetched-pointer case as the
 * then-branch (the ROM's `blt` jumps to the null case, and the `str r0,[r5,#8]`
 * tail is shared), and the two null stores are one chained assignment
 * `*textB = *textA = 0;`. The chain is what puts textB in r6 instead of r7 and
 * matches the ROM's colouring; the reverse order `*textA = *textB = 0;` does
 * not. Those two changes took the diff from REG-only=5 / 16 missing / 11 extra
 * down to REG-only=1 / 13 missing / 8 extra, all of the remainder being the
 * r7 cache and its frame consequences.
 *
 * MsgDb_FetchStringPair: extract the even/odd string pair for logical string
 * `index` of message db `db` (P2_ExtractString at sub-index index*2 and
 * index*2+1). If the record's flag (rec[0]) is negative, store nulls; otherwise
 * cache the two fetched string pointers into rec+4 and rec+8. */
typedef unsigned short u16;
typedef unsigned int u32;

extern int func_02034f44(u16 **out_ptr, u32 *out_count, int db, int k, int keep);

int func_02034fc4(short *rec, u16 **textA, u16 **textB, u32 *lenA, u32 *lenB,
                  int db, int index, int keep) {
    *textB = *textA = 0;
    if (func_02034f44(textA, lenA, db, index * 2, keep) == 0) {
        return 0;
    }
    if (func_02034f44(textB, lenB, db, index * 2 + 1, keep) == 0) {
        return 0;
    }
    if (rec[0] >= 0) {
        *(u32 *)((char *)rec + 4) = *(u32 *)textA;
        *(u32 *)((char *)rec + 8) = *(u32 *)textB;
    } else {
        *(u32 *)((char *)rec + 4) = 0;
        *(u32 *)((char *)rec + 8) = 0;
    }
    return 1;
}
