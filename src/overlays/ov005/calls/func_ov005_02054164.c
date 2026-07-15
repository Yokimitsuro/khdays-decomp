/* func_ov005_02054164 -- spawn the ov005 worker task, ov005 (tail-call to func_0200c4fc
 * with priority 4, stack idx 5, on the boot arena data_0204c024). */
extern int func_0200c4fc(int a, int prio, void *arena, int stackIdx);
extern int data_0204c024;
int func_ov005_02054164(void) {
    return func_0200c4fc(0, 4, &data_0204c024, 5);
}
