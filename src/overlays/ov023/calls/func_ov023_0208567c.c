/* func_ov023_0208567c -- script VM command: run the ov023 step and report whether the command is
 * finished. Finished (1) only when the VM says so AND the flag byte at +0x4a4 of the VM state is
 * clear; if the flag is set the step runs a second time and the command stays alive (0).
 *
 * The two constant returns live OUT OF LINE at the end, which is what the ROM's `beq` to the tail
 * shows; written as plain `return 0;` inside the guard mwcc inlines it and the branch polarity
 * flips. `goto` labels after the body reproduce the layout. */
extern void func_ov023_0208557c(int a, int b);
extern int func_ov002_0205f4b4(void);

int func_ov023_0208567c(int a, int b) {
    func_ov023_0208557c(a, b);
    if (func_ov002_0205f4b4() == 0) {
        goto ret0;
    }
    if (*(signed char *)(*(int *)(a + 0x128) + 0x4a4) == 0) {
        goto ret1;
    }
    func_ov023_0208557c(a, b);
    goto ret0;
ret1:
    return 1;
ret0:
    return 0;
}
