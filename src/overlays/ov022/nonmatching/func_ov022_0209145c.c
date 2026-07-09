/* NONMATCHING: pure register-coloring tie. Structurally identical
 * (push;cmp;popeq;ldr;blx;pop) but the original loads the call target into r2
 * (`ldr r2,[r0,#0x20]; blx r2`) while mwcc reuses the now-dead r0. Byte-exact
 * in the blob. */
void func_ov022_0209145c(int arg0) {
    if (arg0 == 0) return;
    (*(void (**)(void))(arg0 + 0x20))();
}
