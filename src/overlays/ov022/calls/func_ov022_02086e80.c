/* * Was parked as a register-allocation tie. It was not -- it was a THUMB function that had only
 * ever been verified as ARM (giving a nonsense size gap), plus two ordinary steers:
 *   - `i = 0` must be a STATEMENT after the calls, not a declaration-initialiser. As an
 *     initialiser mwcc emits `movs rN, #0` up front; the ROM emits it after the last call.
 *   - declaration order then picks the callee-saved pair: declare `i` BEFORE `p` to get the
 *     ROM's i->r4 / p->r5.
 * The old header's "r4<->r5 coloring swap" was real, but it was a SYMPTOM of the `i = 0`
 * placement, not a compiler limit. (2026-07-17)
 */
extern int func_ov022_02083f0c(void);
extern void func_ov002_02050e64(void);
extern void func_ov002_0205126c(int arg0);
extern void func_ov000_0204cac0(int arg0, int arg1);
extern int data_ov022_020b2e74;

void func_ov022_02086e80(int arg0) {
    int i;
    int p = *(int *)&data_ov022_020b2e74;
    int g = func_ov022_02083f0c();
    func_ov002_02050e64();
    i = 0;
    do {
        if (i < arg0) {
            if ((unsigned int)(*(unsigned char *)(p + 0x2a) << 0x1b) >> 0x1b) {
                func_ov002_0205126c(p);
            }
        }
        i = i + 1;
        p = p + 0x30;
    } while (i < 4);
    func_ov000_0204cac0(g, 0);
}
