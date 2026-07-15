/* func_ov000_0204f7ac -- flag the logo scene block ready, ov000. Runs
 * func_ov000_02054e48, then sets the scene block's ready field (@+0x6a44) to 1. */
extern void func_ov000_02054e48(void);
extern char *data_ov000_0205ac24;
void func_ov000_0204f7ac(void) {
    func_ov000_02054e48();
    *(int *)(data_ov000_0205ac24 + 0x6a44) = 1;
}
