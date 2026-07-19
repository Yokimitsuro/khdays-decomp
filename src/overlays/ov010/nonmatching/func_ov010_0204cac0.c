/* func_ov010_0204cac0 -- zero a 0xc-byte handle and bind it to a resource loaded
 * via func_0201ef9c (Archive_LoadFile). PROVEN register-allocation tie.
 *
 * Semantics fully recovered. The loaded file starts with {offset, count}; the
 * handle ends up as {file, count, file + offset}.
 *
 * The ONLY diff is 8 bytes of tail register coloring: `res` is pinned to r0 by the
 * call ABI, and the survivor `off = res->offset` legally colors to r1 (tight
 * {r0,r1}, what every runnable mwcc build picks) or r2 (loose {r1,r2}, wastes a
 * register -- what the retail ROM emitted). Both are valid 2-colorings.
 *
 *   ROM tail (target):        ours (every compiler, every form):
 *     ldr r2,[r0]               ldr r1,[r0]
 *     ldr r1,[r0,#4]            ldr r0,[r0,#4]
 *     str r1,[r5,#4]            str r0,[r5,#4]
 *     ldr r1,[r5]               ldr r0,[r5]
 *     add r1,r1,r2              add r0,r0,r1
 *     str r1,[r5,#8]            str r0,[r5,#8]
 *
 * RULED OUT (cumulative):
 *  - ALL 5 mwcc build-lines (1.2.x, 2.0.x, 3.0/136, 3.0/139, dsi) x the full
 *    -O/opt-flag matrix x 6 optimizer pragmas x 15 curated source forms x an
 *    81k-iteration AST permuter. None emit r2. See memory reference_mwcc136_unlock.
 *  - A prior pass had func_0201ef9c as a 4-arg call. Wrong: only r0,r1 are set, so
 *    2 args. Fixing that removed 12 wrong bytes and left only this coloring tie.
 *  - * 2026-07-20: the STRUCT/typing axis, which that sweep never tried and which
 *    had just cracked func_ov008_0208b9e8 (where types WERE load-bearing). Six
 *    typed formulations: typed handle + typed file, offset read from the call
 *    result vs from the stored field, `char *` vs `int` payload, declaration
 *    order. The best of them reproduces the ROM's instruction stream EXACTLY --
 *    same ops, same order, same reload of h->file for the add -- and still colors
 *    off to r1. So the structure was never the problem, and typing is not the
 *    lever here. Kept below anyway: it is much better C for the port.
 *
 * Retest only if a new mwcc build is added to the toolkit.
 */
extern void MI_CpuFill8(void *dest, int val, int size);

typedef struct {
    int offset;   /* payload starts this many bytes into the file */
    int count;
} ResFile;

typedef struct {
    ResFile *file;
    int count;
    char *payload;
} ResHandle;

extern ResFile *func_0201ef9c(char *name, int kind);

void func_ov010_0204cac0(ResHandle *h, char *name, int p3, int p4) {
    ResFile *res;
    int off;

    MI_CpuFill8(h, 0, 0xc);
    res = func_0201ef9c(name, 0xe);
    h->file = res;
    off = res->offset;
    h->count = res->count;
    h->payload = (char *)h->file + off;   /* reloads h->file, as the ROM does */
}
