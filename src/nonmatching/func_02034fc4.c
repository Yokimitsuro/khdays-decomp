/* NONMATCHING: semantics correct, optimization tie (90B vs 100B). The ROM re-reads
 * `index` from its stack home and recomputes index*2 / index*2+1 at each of the two
 * P2_ExtractString calls (keeping outB_ptr in r6, one outgoing arg in a sub-sp slot).
 * mwcc 3.0/139 caches index<<1 in a spare callee-saved reg (r7) across the first
 * call, so it doesn't re-read (shorter). No C form un-caches it: index*2, index<<1,
 * and separate-statement sub-indices all keep the common index*2 in a register.
 *
 * MsgDb_FetchStringPair: extract the even/odd string pair for logical string
 * `index` of db `db` (P2_ExtractString at sub-index index*2 and index*2+1). If the
 * record's flag (rec[0]) is negative, store nulls; otherwise store the two fetched
 * string pointers into rec+4 and rec+8. */
extern int func_02034f44(unsigned short **out_ptr, unsigned int *out_count, int db, int k, int keep);
int func_02034fc4(short *rec, unsigned int *outA_ptr, unsigned int *outB_ptr,
                  unsigned int *outA_cnt, unsigned int *outB_cnt, int db, int index, int keep) {
    int val;
    *outA_ptr = 0;
    *outB_ptr = 0;
    if (func_02034f44((unsigned short **)outA_ptr, outA_cnt, db, index << 1, keep) == 0) {
        return 0;
    }
    if (func_02034f44((unsigned short **)outB_ptr, outB_cnt, db, index * 2 + 1, keep) == 0) {
        return 0;
    }
    val = 0;
    if (rec[0] < 0) {
        *(int *)((int)rec + 4) = 0;
    } else {
        *(int *)((int)rec + 4) = *(int *)outA_ptr;
        val = *(int *)outB_ptr;
    }
    *(int *)((int)rec + 8) = val;
    return 1;
}
