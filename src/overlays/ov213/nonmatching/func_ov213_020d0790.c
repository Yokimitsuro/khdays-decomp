/* NON-MATCHING: the inline-memcpy pointer-register swap already filed for ov213_020cbfc8.
 *
 * Refresh the shared transform, then publish this actor's 11-word matrix (obj+0xa0) into its
 * render node (*(obj+0x390))+0x10.
 *
 * Everything matches except which register carries the load pointer and which the store pointer
 * in mwcc's inline struct copy:
 *      ROM : add lr,r4,#0xa0 ; add ip,r0,#0x10 ; ldm lr!,{...} ; stm ip!,{...}
 *      mwcc: add ip,r4,#0xa0 ; add lr,r0,#0x10 ; ldm ip!,{...} ; stm lr!,{...}
 * i.e. the ROM puts the SOURCE in lr and the DEST in ip, every mwcc build does the opposite.
 * Unlike ov213_020cbfc8 the two address computations are already emitted in the ROM's order here,
 * so only the register roles differ; hoisting either side into an explicit `Mtx11 *` local (dst
 * first or src first) does not move them.
 *
 * This is the same compiler-version difference as ov213_020cbfc8 (build_sweep: 24 off on all 27
 * builds there), and it blocks the whole matrix-publish shape: ov213_020d0790 / ov273_020d43d0
 * (byte-identical twins) plus the same-shape ov253_020d3c78, ov258_020cfef4 and ov283_020cef04,
 * which differ only in the render-node offset (0x39c / 0x390). Do not re-attempt without a new
 * compiler build.
 */

typedef struct { int a[11]; } Mtx11;

extern void func_ov107_020c6980(void);

void func_ov213_020d0790(int obj) {
    func_ov107_020c6980();
    *(Mtx11 *)(*(int *)(obj + 0x390) + 0x10) = *(Mtx11 *)(obj + 0xa0);
}
