/* NONMATCHING: 148B vs 152B -- one instruction. Structure, the variadic prologue
 * (stmdb sp!,{r0,r1,r2,r3}), the predicated Q12 stores and every call all match.
 * The ROM pushes {r3,r4,r5,lr} and keeps BOTH panel (r5) and idx (r4) in callee-saved
 * registers; mwcc 3.0/139 keeps only panel and re-reads idx from the argument spill slot
 * that va_start already forced into memory -- one 'mov r4,r1' fewer. That is the
 * "our compiler is smarter" tie family (see references/deferred-ties.md): mwcc exploits a
 * memory copy the ROM's compiler duplicated into a register.
 *
 * NOTE: this is the FIRST variadic function decompiled in this project. mwcc has no
 * stdarg.h on our include path; the APCS macros below are correct and reproduce the ROM's
 * prologue exactly. Reuse them for the next one.
 *
 * func_ov006_02051fbc -- Mission Mode: place cell `idx` of panel `panel`.
 * Variadic: takes x, y, cell id and a suppress flag. A negative x or y means "leave at 0";
 * both are converted to Q12. A non-negative id with the flag clear re-binds the cell to that
 * graphic and drops it from the draw list first. */
/* mwcc has no stdarg.h on this include path; the standard ARM APCS definitions. */
typedef char *va_list;
#define va_start(ap, last) ((ap) = (char *)&(last) + sizeof(last))
#define va_arg(ap, type)   (*(type *)(((ap) += sizeof(type)) - sizeof(type)))
#define va_end(ap)         ((void)0)

extern void func_020325ec(int panel, int idx, int cell);
extern void func_020326cc(int panel, int idx);
extern void func_0203257c(int panel, int idx, int *pos);

void func_ov006_02051fbc(int panel, int idx, ...) {
    int pos[2];
    va_list ap;
    int x, y, cell, keep;

    va_start(ap, idx);
    x = va_arg(ap, int);
    y = va_arg(ap, int);

    pos[0] = 0;
    pos[1] = 0;
    if (x >= 0) {
        pos[0] = x << 12;
    }
    if (y >= 0) {
        pos[1] = y << 12;
    }
    cell = va_arg(ap, int);
    keep = va_arg(ap, int);
    va_end(ap);
    if (cell >= 0 && keep == 0) {
        func_020325ec(panel, idx, cell & 0xffff);
        func_020326cc(panel, idx);
    }
    func_0203257c(panel, idx, pos);
}
