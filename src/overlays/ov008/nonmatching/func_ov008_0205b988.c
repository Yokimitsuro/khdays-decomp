/* Compute the 3-way "fill level" of a gauge: base level (page+0x14f3), optionally boosted by the
 * node's own bonus (+0x15) when its stat slot reads < 2, then bumped past two page thresholds
 * (0x14f0, then +0x14f1). Store the result (1..3) at data_0204c300[0x4f].
 *
 * NON-MATCHING (equivalent). Several compiler-choice residues compound: (1) the ROM materialises
 * the `GetField(...) < 2` guard as a bool (movcs/movcc + cmp #0) instead of the direct predicated
 * `ldrblt` mwcc emits; (2) the two threshold compares use `hi` (unsigned, level>byte) then `gt`
 * (signed, level>byte+byte) with `and #0xff` after each bump, whereas mwcc reverses the operands to
 * `lo`/`lo` and sign-extends the char result. No single type spelling reconciles the unsigned-then-
 * signed compare pair with the byte-masked increments. */
extern int func_ov008_02050cd4(void);
extern int func_020235d0(int field, int size);
extern unsigned char data_0204c300[];

void func_ov008_0205b988(int param_1) {
    int page = func_ov008_02050cd4();
    unsigned int level = *(unsigned char *)(page + 0x14f3);
    char result;
    if (param_1 != 0 &&
        func_020235d0(*(unsigned short *)(param_1 + 2) * 3 + 0x28e4, 3) < 2) {
        level = (level + *(unsigned char *)(param_1 + 0x15)) & 0xff;
    }
    result = 1;
    if (*(unsigned char *)(page + 0x14f0) < level) {
        result = 2;
    }
    if ((unsigned int)*(unsigned char *)(page + 0x14f1) + *(unsigned char *)(page + 0x14f0) < level) {
        result = result + 1;
    }
    *(char *)(data_0204c300 + 0x4f) = result;
}
