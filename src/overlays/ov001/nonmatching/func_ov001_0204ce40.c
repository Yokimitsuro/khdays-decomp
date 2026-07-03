/* NONMATCHING — semantically-equivalent C, kept out of the byte-exact build.
 *
 * Why it can't match with our toolchain: the original loads the constant 0x1c
 * via `ldr r4,[pc,#0x10c]` from the literal pool (no reloc) and holds it in a
 * callee-saved register across the whole function. Empirically probed EVERY
 * mwccarm we have (1.2 base..sp4, 2.0 base..sp2p4, 3.0_136, 3.0_patch4) at
 * -O0/-O1/-O2/-O3/-O4/-O4,p, as int and as pointer constant: they ALWAYS emit
 * `mov r1,#0x1c` (encodable immediate), never a pool load. Conclusion: in the
 * original source 0x1c was a LINKER-ASSIGNED ABSOLUTE SYMBOL (an SDK lock id),
 * so the compiler saw an opaque address constant; dsd cannot re-derive a reloc
 * from the small integer. Matching would need an absolute symbol in the LCF +
 * final-ROM-level validation. The asm stub stays authoritative for linking.
 *
 * Semantics: sound-heap bootstrap. Under lock id 0x1c: if func_0208b490 says a
 * (streaming?) player exists, allocate 0xC8000 bytes (16-aligned) for it; then
 * size the remaining arena (func_020029bc = lo, func_020029a8 = hi) and give
 * the second allocation either half of it or all of it depending on four
 * player-mode predicates. Returns both buffers via out-params.
 */
extern void func_0200b6ac(int a, int b);
extern int func_0208b490(int a);
extern int func_02002b84(int a, int b, int c);
extern void *func_020107b8(int a, int b, int c);
extern int func_020029bc(int a);
extern int func_020029a8(int a);
extern int func_0208b200(int a);
extern int func_0208b040(int a);
extern int func_0208b120(int a);
extern int func_0208b2e0(int a);
extern void func_0200b700(int a, int b);
#define SND_LOCK_ID 0x1c /* linker-absolute in the original build */
void func_ov001_0204ce40(void **outMainBuf, void **outSubBuf) {
    void *mainBuf = 0, *subBuf = 0;
    unsigned arenaHi, arenaLo;
    int size;
    func_0200b6ac(0, SND_LOCK_ID);
    if (func_0208b490(0) != 0)
        mainBuf = func_020107b8(func_02002b84(0, 0xc8000, 0x10), 0xc8000, 0);
    arenaLo = (func_020029bc(0) + 0xf) & 0xfffffff0;
    arenaHi = func_020029a8(0);
    if (func_0208b200(0) == 0 && func_0208b040(0) == 0) {
        if (func_0208b120(0) != 0 && func_0208b2e0(0) != 0) {
            size = (arenaHi & 0xfffffff0) - arenaLo;
            subBuf = func_020107b8(func_02002b84(0, size, 0x10), size, 0);
        }
    } else {
        size = ((arenaHi & 0xfffffff0) - arenaLo) >> 1;
        subBuf = func_020107b8(func_02002b84(0, size, 0x10), size, 0);
    }
    func_0200b700(0, SND_LOCK_ID);
    *outMainBuf = mainBuf;
    *outSubBuf = subBuf;
}
