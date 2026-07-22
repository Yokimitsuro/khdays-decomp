/* Linear-scan the entry table at +0x88 (stride 0x80, count at +0x8c) for the first entry whose
 * kind byte at +3 matches, and answer its data pointer plus 4; 0 when nothing matches.
 *
 * Parked as a register-coloring plus strength-reduction tie: the original re-loads the table
 * pointer inside the loop and recomputes `base + i*0x80` each iteration, while mwcc hoisted the
 * load and walked a pointer. Declaring the table as a real array of structs stops the reduction,
 * and the declaration order does the rest -- with the counter, the result and the table pointer
 * declared before the limit, the four values land where the original has them. The other 23
 * orderings are byte-identical apart from which register each local gets. */
struct Ov022Ent {
    char _pad0[3];
    unsigned char bKind;        /* +0x03 */
    char _pad4[0x38 - 4];
    int pData;                  /* +0x38 */
    char _pad3c[0x80 - 0x3c];
};
struct Ov022Owner {
    char _pad0[0x88];
    struct Ov022Ent *pTable;    /* +0x88 */
    int nCount;                 /* +0x8c */
};

int func_ov022_020b0ba8(struct Ov022Owner *owner, unsigned int kind) {
    int r;
    int i;
    struct Ov022Ent *tb;
    int lim;

    lim = owner->nCount;
    r = 0;
    i = 0;
    if (lim > 0) {
        do {
            tb = owner->pTable;
            if (kind == tb[i].bKind) {
                r = tb[i].pData + 4;
                break;
            }
            i++;
        } while (i < lim);
    }
    return r;
}
