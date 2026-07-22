/* func_ov000_0204df98 -- Scene 1 (boot/logo) hand-off state, ov000.
 * A 3-phase sub-state machine (phase counter = u16 at heap+0x4c50) that waits for
 * the next scene to become ready before advancing:
 *   phase 0: reset the retry/attempt counters (heap+0x4c52/+0x4c53), run
 *            func_ov000_02054e48, force both screens dark, phase++.
 *   phase 1: poll func_ov000_02054e7c and act on its result (retry bookkeeping;
 *            on result 3 re-instantiate the scene class @data_ov000_0205a9c0; on
 *            result 0 probe func_020235d0 and set a flag). Once the attempt counter
 *            (heap+0x4c52) reaches 3, phase++.
 *   phase 2: advance to func_ov000_0204e270.
 * Any other phase (and the fall-through of 0/1) returns 0 (stay). 
 *
 * Both calls to func_ov000_02054e48 pass an argument: the extern here said `(void)` and the
 * definition takes one (tools/audit_extern_sig.py names it). In phase 0 the argument is the same
 * 0 the two byte fields are cleared with -- one constant doing double duty, which is why it looks
 * argument-free -- and in phase 1 it is the freshly incremented attempt counter, the very value
 * the `< 3` test compares. Binding that increment to a local is what makes the ROM's
 * `and r0,r2,#0xff` serve both the compare and the call.
 */

typedef void *StateFn;

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void  func_ov000_02054e48(int a);
extern int   func_ov000_02054e7c(void);
extern int   func_020235d0(int, int);
extern void  func_02023930(void *classDesc, int arg);
extern void  func_0201e374(int brightness);
extern void  func_0201e3cc(int brightness);
extern char  data_ov000_0205a9c0[];
extern void  func_ov000_0204e270(void);

StateFn func_ov000_0204df98(void) {
    char *h = (char *)NNSi_FndGetCurrentRootHeap();
    unsigned short phase = *(unsigned short *)(h + 0x4c50);
    switch (phase) {
    case 0:
        *(unsigned char *)(h + 0x4c53) = 0;
        *(unsigned char *)(h + 0x4c52) = 0;
        func_ov000_02054e48(0);
        func_0201e374(0x10);
        func_0201e3cc(0x10);
        (*(unsigned short *)(h + 0x4c50))++;
        break;
    case 1:
        switch (func_ov000_02054e7c()) {
        case 3:
            func_02023930(data_ov000_0205a9c0, 2);
            break;
        case 0:
            if (func_020235d0(0x44e, 3) == 6) {
                *(int *)(h + 0x4c54) |= 1;
            }
            /* fallthrough */
        case 4:
            (*(unsigned char *)(h + 0x4c53))++;
            /* fallthrough */
        case 2:
            {
                unsigned char n = ++*(unsigned char *)(h + 0x4c52);
                if (n < 3) {
                    func_ov000_02054e48(n);
                }
            }
            break;
        }
        if (*(unsigned char *)(h + 0x4c52) >= 3) {
            (*(unsigned short *)(h + 0x4c50))++;
        }
        break;
    case 2:
        return (StateFn)func_ov000_0204e270;
    }
    return 0;
}
