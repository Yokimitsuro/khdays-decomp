/* func_ov025_0209ef34 -- is row `idx` of the ov025 flag table free? The table lives at +0xa11 of
 * the shared block and the row is 1-based.
 * The three constants are added in TWO statements on purpose: written as one expression mwcc folds
 * `+1 +0x200 +0x810` into a single `add #0xa11`, where the ROM keeps `add #1 ; add #0xa00` and the
 * remaining 0x810 in the load. Splitting the additions is what keeps them apart. */
extern int data_0204be18;

int func_ov025_0209ef34(int idx) {
    int off = idx + 1;
    off = off + 0x200;
    return *(unsigned char *)(*(int *)&data_0204be18 + off + 0x810) == 0;
}
