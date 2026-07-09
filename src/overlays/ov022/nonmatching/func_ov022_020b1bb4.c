/* NONMATCHING: constant-materialization tie. The original builds 0xff as
 * `sub r0, r1, #1` reusing the r1=0 held for the other zero stores; mwcc emits
 * `mov #0xff` / `mvn #0` from 0xff, -1, or `z-1` (all folded). Byte-exact in
 * the blob. */
extern int func_ov022_020b1b88(int);   /* ov022_IsByte8ZeroOr3 */
void func_ov022_020b1bb4(int arg0) {
    if (!func_ov022_020b1b88(arg0)) return;
    *(unsigned char *)(arg0 + 8) = 0;
    *(unsigned char *)(arg0 + 10) = 0xff;
    *(unsigned char *)(arg0 + 0xb) = 0xff;
    *(unsigned char *)(arg0 + 0xe) = 0;
    *(unsigned char *)(arg0 + 9) = 0;
}
