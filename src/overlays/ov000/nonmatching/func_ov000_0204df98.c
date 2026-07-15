/* func_ov000_0204df98 -- Scene 1 (boot/logo) hand-off state, ov000.
 * NONMATCHING: semantically byte-exact except one scratch-register permutation
 * (r1<->r2 on base vs increment-temp) in the phase-1 case-2 counter bump; every
 * other instruction matches. mwcc keeps the live compared value in r0 and the
 * base in r1 there; no C form reproduces the exact r1/r2 pairing without changing
 * the instruction count. Kept here for the PC port (logic is exact).
 *
 * A 3-phase sub-state machine (phase counter = u16 at heap+0x4c50) that waits for
 * the next scene to become ready before advancing:
 *   phase 0: reset the retry/attempt counters (heap+0x4c52/+0x4c53), run
 *            func_ov000_02054e48, force both screens dark, phase++.
 *   phase 1: poll func_ov000_02054e7c and act on its result (retry bookkeeping;
 *            on result 3 re-instantiate the scene class @data_ov000_0205a9c0; on
 *            result 0 probe func_020235d0 and set a flag). Once the attempt counter
 *            (heap+0x4c52) reaches 3, phase++.
 *   phase 2: advance to func_ov000_0204e270.
 * Any other phase (and the fall-through of 0/1) returns 0 (stay). */

typedef void *StateFn;

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void  func_ov000_02054e48(void);
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
        func_ov000_02054e48();
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
            if (++*(unsigned char *)(h + 0x4c52) < 3) {
                func_ov000_02054e48();
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
