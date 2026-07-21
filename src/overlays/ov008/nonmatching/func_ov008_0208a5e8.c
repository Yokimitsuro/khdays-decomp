/* Item-ID validity test: an id is valid (1) when it is below 0x201 and not one of the excluded
 * singletons {1, 0x1a0, 0x1c8, 0x1c9}; otherwise 0.
 *
 * NON-MATCHING (equivalent). Correct size (88) and semantics; the outer 0x1a0 test and the
 * 0x1c8 bound match. Residue is our build 139 optimising harder than the ROM's compiler in two
 * spots: (a) it collapses `id==0x1a0 || id==1` into a single flag-reusing `cmpne #1; bne`
 * (falling into an inline `return 0`) where the ROM keeps a `bge` + separate `cmp #1; beq` into a
 * shared return-0 block; (b) it range-folds `id==0x1c8 || id==0x1c9` into `(unsigned)(id-0x1c8)
 * <= 1` where the ROM keeps explicit `cmpne r0,r1; bne`. Both are branch/flag heuristics; no
 * source spelling of the same predicate suppresses them under our flags. */
int func_ov008_0208a5e8(int id) {
    if (id <= 0x1a0) {
        if (id == 0x1a0 || id == 1) {
            return 0;
        }
    } else if (id <= 0x1c9 && id >= 0x1c8 && (id == 0x1c8 || id == 0x1c9)) {
        return 0;
    }
    return id < 0x201 ? 1 : 0;
}
