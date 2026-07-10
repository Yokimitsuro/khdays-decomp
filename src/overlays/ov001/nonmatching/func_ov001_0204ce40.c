/* NONMATCHING — semantically-equivalent C, kept out of the byte-exact build.
 *
 * The real blocker (found 2026-07-10, see docs/ov028_encrypted_code.md): this
 * function makes three cross-overlay calls to ov028 at 0x0208b490 / 0x0208b200 /
 * 0x0208b040, which are SELF-DECRYPTING ANTI-TAMPER functions. In the static ROM
 * their bodies are encrypted (they don't decode as ARM), so dsd cannot attribute
 * the calls to a module and emits them as `module:none` raw `bl`s with no reloc.
 * You cannot link a matched C .c against a target that isn't code on disk, so the
 * asm stub stays authoritative. This is a format/protection limit, not a codegen
 * tie — it affects 17 module:none relocs across ov000/ov001/ov004/ov005/ov023.
 *
 * Secondary issue (real but moot until the above is solvable): the constant 0x1c
 * loads via `ldr r4,[pc,#0x10c]` from the pool (no reloc). mwcc always emits
 * `mov r1,#0x1c` for a literal; only referencing the ADDRESS of an extern symbol
 * forces the pool load. In the original 0x1c was a linker-absolute lock id.
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
