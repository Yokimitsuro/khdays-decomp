/* Equivalent, readable C. NOT byte-exact: this 428B HUD row-layout routine hits
 * several unsteerable codegen ties at -O4 — mwcc strength-reduces the `col`
 * counter (col*0x40) into a stride-0x80 induction var (the original keeps `col`
 * and does `col<<6` at each use), plus a different callee-saved coloring of
 * `off`/pool and second-loop induction. Structure and size are otherwise a near
 * match (452 vs 428). The asm stub keeps the blob byte-exact.
 */
extern char data_ov003_0204f9a0[];
extern void func_02013484(int a0, unsigned short *a1, int a2, int a3, int a4,
                          int a5, int a6, int a7, int a8, int a9);
extern int func_ov003_0204cadc(int mode);
extern void func_ov003_0204d1c0(unsigned short *dst, unsigned int value);
extern void func_ov003_0204d264(unsigned short *dst, unsigned int value, int pal);

#define CTX (*(int *)data_ov003_0204f9a0)

/* Lay out one panel row (index `param_1`) of the ov003 status HUD: draw the
 * label tilemap, patch two palette-indexed name tiles, render the four numeric
 * fields, then fill the 6x6 background tile block. */
void func_ov003_0204d3b0(int param_1) {
    int off = func_ov003_0204cadc(param_1);
    int i;
    int col;
    int j;
    unsigned int uv;

    func_02013484(CTX + 0x17b8, *(unsigned short **)(CTX + 0x1dc0), 0, 0, off,
                  3, 0x20, 0x18, 8, 0x12);

    *(unsigned short *)(CTX + (off + 1) * 2 + 0x1878) =
        *(unsigned short *)(CTX + (off + 1) * 2 + 0x1878) & 0xf000 |
        (*(unsigned char *)(CTX + param_1 + 2) * 2 + 1);
    *(unsigned short *)(CTX + (off + 2) * 2 + 0x1878) =
        *(unsigned short *)(CTX + (off + 2) * 2 + 0x1878) & 0xf000 |
        (*(unsigned char *)(CTX + param_1 + 2) * 2 + 2);

    col = 0xc;
    i = 0;
    do {
        if (i == 0) {
            func_ov003_0204d1c0((unsigned short *)(CTX + 0x1ab8 + (off + 2) * 2),
                                *(unsigned short *)(CTX + param_1 * 8 + 10));
        } else {
            func_ov003_0204d264((unsigned short *)(CTX + 0x17b8 + col * 0x40 + (off + 4) * 2),
                                *(unsigned short *)(CTX + param_1 * 8 + i * 2 + 10), 0xb);
        }
        i = i + 1;
        col = col + 2;
    } while (i < 4);

    uv = (param_1 * 0x24 + 0x100) & 0xffff;
    j = 0;
    do {
        int k = 0;
        do {
            *(unsigned short *)(CTX + j * 0x40 + off * 2 + k * 2 + 0x18ba) =
                (unsigned short)uv | (param_1 + 1) * 0x1000;
            uv = (uv + 1) & 0xffff;
            k = k + 1;
        } while (k < 6);
        j = j + 1;
    } while (j < 6);
}
