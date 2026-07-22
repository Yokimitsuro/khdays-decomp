/* BootTask_Construct: constructor of g_BootTaskClassDesc (run by RunClassConstructor).
 * Inits subsystems, then selects the first scene from the persisted state word @0x027ffc20:
 * 0 (fresh boot) -> Scene 1 (boot/logo); -2 -> Scene 1; else -> Scene 12. The scene request
 * is latched by func_02020a78 (StoreGlobalPairAt10). Returns the boot task's initial
 * per-frame state fn (func_02020978), stored by the caller into obj+0x14.
 *
 * The 4 bytes that kept this parked were the second branch pair: the ROM emits
 * `beq c ; b d` and every if/goto spelling of the chain gave mwcc's `bne d ; b c`.
 * `beq X ; beq Y ; b Z` is the SWITCH compare-chain shape, not an if-chain shape -- so this
 * wants a switch. The old note rejected the switch for the right reason and the wrong
 * conclusion: mwcc orders a switch's compare chain NUMERICALLY, so with `case 0` and
 * `case -2` on a SIGNED selector it tests -2 first, which is backwards. Read the selector
 * as UNSIGNED and the same two cases become 0 and 0xfffffffe, so 0 is tested first and the
 * chain comes out in the ROM's order. The numeric ordering is not an obstacle -- it is the
 * knob. */
extern void func_0201ea6c(void);
extern void func_020333c8(int a);
extern void func_02033500(int a);
extern void func_02020988(void);
extern void func_02020a78();
extern int func_02020978(void);

void *func_02020928(void) {
    unsigned int state;
    func_0201ea6c();
    func_020333c8(0);
    func_02033500(0);
    func_02020988();
    state = *(unsigned int *)0x027ffc20;
    switch (state) {
    case 0:
        func_02020a78(1, 0);
        break;
    case 0xfffffffeu:
        func_02020a78(1, state);
        break;
    default:
        func_02020a78(0xc, state);
        break;
    }
    return (void *)func_02020978;
}
