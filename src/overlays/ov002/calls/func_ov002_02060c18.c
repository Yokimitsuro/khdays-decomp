/* Emit the local player's box, biased by the panel, and advance the caller's cursor.
 *
 * The box is twelve bytes and is copied onto the stack before being touched, so the source stays
 * as it was. Only the middle word is changed, by adding the panel's own field to it, and the
 * caller's second word moves on by 0xa000 once the box has been emitted.
 *
 * The two lookups stay nested inside the copy call rather than being held in locals, which is what
 * lets each result flow straight through the argument register.
 *
 * Ghidra carries the box as Ov002EmitBox.
 */

typedef unsigned int u32;

extern int func_02030788(void);
extern void *func_ov022_020881f8(int player);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern int func_ov002_020575b0(void);
extern void func_ov002_02060b4c(int *out, int *box, int arg);

void func_ov002_02060c18(int *out, int arg) {
    int box[3];

    MI_CpuCopy8(func_ov022_020881f8(func_02030788()), box, 0xc);
    box[1] += func_ov002_020575b0();
    func_ov002_02060b4c(out, box, arg);
    out[1] += 0xa000;
}
