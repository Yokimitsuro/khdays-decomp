/* func_ov253_020d1cf0 -- forward event 4 to the owner's handler, with the context's +0x20 block as
 * the payload. Nothing happens unless the owner has a handler at +0x74.
 * The handler must be loaded AFTER the payload call: binding the call's result to a local first is
 * what puts the ROM's `bl` before the `ldr r3,[r4,#0x74]`. Written inline as the callee expression
 * of the indirect call, mwcc loads the handler first and the function is 4 bytes short. */
extern int OS_IsThreadAvailable_0x020c9848();
extern int func_ov022_02083f0c(void);

void func_ov253_020d1cf0(int self) {
    int ctx = *(int *)(self + 4);
    int obj;
    int arg;
    if (*(int *)(OS_IsThreadAvailable_0x020c9848(self) + 0x74) == 0) {
        return;
    }
    obj = OS_IsThreadAvailable_0x020c9848();
    arg = func_ov022_02083f0c();
    (*(void (**)(int, int, int))(obj + 0x74))(arg, 4, ctx + 0x20);
}
