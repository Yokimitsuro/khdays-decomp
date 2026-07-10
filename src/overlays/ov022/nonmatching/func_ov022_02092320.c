/*
 * [nonmatching: reloaded-base register-coloring tie — 52B, structurally byte-identical]
 *
 * Ref-counted init: if data_ov022_020b2eac is 0, registers func_ov022_02091f8c
 * via func_02030cf8; increments the count; then zeroes 6 words at arg0.
 *
 * After the func_02030cf8 call, the counter's address is reloaded from the pool
 * for the `*count += 1` RMW. The original colors that reloaded base into r0 and
 * the value into r1 (`ldr r0,[pc]; ldr r1,[r0]; adds r1,#1; str r1,[r0]`); mwcc
 * 3.0/139 picks the opposite (base r1, value r0). Identical instructions, only
 * r0<->r1 swap on the increment. A held pointer instead spills to a callee-saved
 * reg (+4B, extra push); inline leaves the swap. Unsteerable — left uncarved
 * (byte-exact in the blob). Sibling 02092354 (decrement form) matches.
 */
extern void func_02030cf8(int arg0, int arg1);
extern int data_ov022_020b2eac;
extern void func_ov022_02091f8c(void);

void func_ov022_02092320(int *arg0) {
    int i;
    if (*(int *)&data_ov022_020b2eac == 0) {
        func_02030cf8(10, (int)func_ov022_02091f8c);
    }
    *(int *)&data_ov022_020b2eac = *(int *)&data_ov022_020b2eac + 1;
    i = 0;
    do {
        i = i + 1;
        *arg0 = 0;
        arg0 = arg0 + 1;
    } while (i < 6);
}
