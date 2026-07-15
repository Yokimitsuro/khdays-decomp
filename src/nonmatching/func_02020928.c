/* BootTask_Construct: constructor of g_BootTaskClassDesc (run by RunClassConstructor).
 * Inits subsystems, then selects the first scene from the persisted state word @0x027ffc20:
 * 0 (fresh boot) -> Scene 1 (boot/logo); -2 -> Scene 1; else -> Scene 12. The scene request
 * is latched by func_02020a78 (StoreGlobalPairAt10). Returns the boot task's initial
 * per-frame state fn (func_02020978), stored by the caller into obj+0x14. */
extern void func_0201ea6c(void);
extern void func_020333c8(int a);
extern void func_02033500(int a);
extern void func_02020988(void);
extern void func_02020a78();
extern int func_02020978(void);

void *func_02020928(void) {
    int state;
    func_0201ea6c();
    func_020333c8(0);
    func_02033500(0);
    func_02020988();
    state = *(int *)0x027ffc20;
    if (state == 0) goto a;
    if (state == -2) goto c;
    goto d;
a:
    func_02020a78(1, 0);
    goto end;
c:
    func_02020a78(1);
    goto end;
d:
    func_02020a78(0xc);
end:
    return (void *)func_02020978;
}
