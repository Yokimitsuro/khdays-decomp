/* func_ov010_0204cac0 — zero a 0xc-byte handle and bind it to a resource loaded
 * via func_0201ef9c. PROVEN register-allocation tie → belongs in nonmatching/.
 *
 * Semantics fully recovered and correct. The ONLY diff vs the ROM is 8 bytes of
 * tail register coloring: `res` is pinned to r0 by the call ABI; the survivor
 * `v = res[0]` legally colors to r1 (tight {r0,r1}, what every runnable mwcc build
 * picks) or r2 (loose {r1,r2}, wastes a register — what the retail ROM emitted).
 * Both are valid 2-colorings. Disproven-reachable across ALL 5 mwcc build-lines
 * (1.2.x, 2.0.x, 3.0/136, 3.0/139, dsi) x full -O/opt-flag matrix x 15 curated
 * source forms x 6 MWCC optimizer pragmas x an 81k-iteration AST permuter — none
 * emit r2. See memory reference_mwcc136_unlock. Retest only if a new mwcc build is
 * added to the toolkit.
 *
 * (A prior pass had func_0201ef9c as a 4-arg call — wrong: only r0,r1 are set = 2
 * args; fixing that removed 12 wrong bytes, leaving only this coloring tie.)
 *
 * ROM tail (target):        MINE (all our compilers):
 *   ldr r2,[r0]               ldr r1,[r0]
 *   ldr r1,[r0,#4]            ldr r0,[r0,#4]
 *   str r1,[r5,#4]            str r0,[r5,#4]
 *   ldr r1,[r5]              ldr r0,[r5]
 *   add r1,r1,r2              add r0,r0,r1
 *   str r1,[r5,#8]            str r0,[r5,#8]
 */
extern void MI_CpuFill8(void *dest, int val, int size);
extern int *func_0201ef9c(char *name, int kind);

void func_ov010_0204cac0(unsigned int *handle, char *name, int param3, int param4) {
    int *res;
    int v;
    MI_CpuFill8(handle, 0, 0xc);
    res = func_0201ef9c(name, 0xe);
    handle[0] = (unsigned int)res;
    v = res[0];
    handle[1] = res[1];
    handle[2] = handle[0] + v;
}
