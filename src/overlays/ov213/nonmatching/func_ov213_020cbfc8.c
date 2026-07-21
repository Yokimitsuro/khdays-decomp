/* NON-MATCHING: inline-memcpy register-allocation tie (twin ov273_020cfc08 ties identically).
 *
 * Push the animated bone matrix (11 words at src+4, src = *(ctx+0x3e8)) into three consumers: the
 * two render nodes at *(ctx+0x3d8) and **(ctx+0x3d4) (each at +0x10), and the collision proxy at
 * *(*(ctx+0x430)+0x18) (at +4). src is reloaded before each copy.
 *
 * The chunking (ldm/stm of 4,4,3 words) and the base-load order are byte-exact. The only residue
 * is which register holds the load pointer vs the store pointer in mwcc's inline struct copy:
 * the ROM uses `ldm lr!` (src) / `stm r4!` (dst), every one of our 27 mwcc builds emits the
 * swap `ldm r4!` (src) / `stm lr!` (dst). Declaring dst-first, an explicit dst pointer, and an
 * explicit src pointer all leave the swap; build_sweep reports "24 off" on every build. The
 * retail compiler's memcpy template assigns the two pointers the opposite way -- a compiler-
 * version difference, not a source defect.
 */

typedef struct { int a[11]; } Mtx11;

void func_ov213_020cbfc8(int param_1, int param_2) {
    int dst;
    dst = *(int *)(param_2 + 0x3d8);
    *(Mtx11 *)(dst + 0x10) = *(Mtx11 *)(*(int *)(param_2 + 0x3e8) + 4);
    dst = **(int **)(param_2 + 0x3d4);
    *(Mtx11 *)(dst + 0x10) = *(Mtx11 *)(*(int *)(param_2 + 0x3e8) + 4);
    dst = *(int *)(*(int *)(param_2 + 0x430) + 0x18);
    *(Mtx11 *)(dst + 4) = *(Mtx11 *)(*(int *)(param_2 + 0x3e8) + 4);
}
