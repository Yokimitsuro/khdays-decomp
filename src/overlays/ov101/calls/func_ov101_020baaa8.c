/*
 * Apply a mode change to the actor (multiplayer/link variant).
 *
 * `mode - 0x2e` picks a per-mode arm; each arm no-ops when the mode did not change (+0x6bc
 * caches it). 0x2e re-inits; 0x2f rebinds the block at base+0x2c80; 0x30/0x31 set that block's
 * flag word to 0/1 -- and for 0x31 only, if the actor's slot byte (+8) is the current owner
 * (02030788), clear the block's +0x120 -- then re-arm via 020b4198. Afterwards the mode is
 * handed down (020a384c) and forwarded to the UI: at/above 0x2e it is translated first
 * (020519b0 -> 02052024), below it goes straight through (020521a4).
 *
 * ★ THIS FILE WAS PARKED IN nonmatching/ ON A WRITE-UP THAT WAS WRONG IN ITS PREMISE, and the
 * write-up is worth more than the match. It claimed 020521a4 takes FIVE arguments and that the
 * ROM's `push {r3, r4, r5, r6, r7, lr}` was homing param_4 into the arg5 slot for free -- a tidy
 * story that cost 24 bytes of "unexplainable" gap and blocked four functions.
 *
 * Both halves were wrong, and the callee's own prologue settles it in ten seconds:
 *   020521a4:  64 B, `push {r3,r4,r5,r6,r7,lr}`, never reads [sp,#0x18]  -> FOUR args.
 *              Its push of r3 is ALIGNMENT PADDING: 5 saved regs + lr is odd.
 *   02052024:  `push {...9 regs}` + `sub sp,#4`, then `ldr r0,[sp,#0x28]` -> FIVE args.
 * The push here really does do double duty -- but for 02052024 (see the `str r0,[sp]` before it,
 * with no `sub sp`), and it is about the OUTGOING slot, not about param_4, which does not exist:
 * this function takes two arguments.
 *
 * The lesson generalises past the arity rule already in the skill ("a dropped trailing argument
 * does not change the size"). Here the arity was invented in the OTHER direction -- a phantom
 * fifth argument -- and the tell was the same one I wrote down and then read backwards: the ROM
 * has no `sub sp,#4`, so it has no outgoing arg area to spare, so the call could not have had a
 * fifth argument. Read the callee's prologue; do not infer arity from the caller's push list.
 *
 * The last two instructions came from catalogued spellings:
 *  - the owner-clear stores through the block pointer (`(char *)p + 0x120`), not through the
 *    absolute base+0x2da0; the ROM's `streq r0,[r4,#0x120]` says which base it kept.
 *  - the branch order is inverted from the obvious reading: the `>= 0x2e` arm is written FIRST
 *    and returns, leaving the 020521a4 call as the tail (ROM `blt`, not `bge`).
 *  - the UI loop flag is `flag = 0; if (x == 2) flag = 1;`, not `flag = (x == 2)`.
 */
extern int data_ov101_020bc0e0;

extern void WM_EndKeySharing_0x020bb010(int self);
extern void func_ov101_020bb724(int self, int p);
extern unsigned short func_02030788(void);
extern void func_ov101_020bb738(int self, int p);
extern void func_ov022_020a384c(int self, int mode);
extern int func_ov002_020519b0(int a, int b, int c);
extern void func_ov002_02052024(void *a, int b, int c, int d, int e);
extern void func_ov002_020521a4(void *a, int b, int c, int d);

void func_ov101_020baaa8(int self, int mode) {
    int base = data_ov101_020bc0e0;
    int *p = (int *)(base + 0x2c80);
    int flag;
    int ret;

    switch (mode - 0x2e) {
    case 0:
        if (*(int *)(self + 0x6bc) != mode) {
            WM_EndKeySharing_0x020bb010(self);
        }
        break;
    case 1:
        if (*(int *)(self + 0x6bc) != mode) {
            func_ov101_020bb724(self, (int)p);
        }
        break;
    case 2:
    case 3:
        if (*(int *)(self + 0x6bc) != mode) {
            if (mode == 0x30) {
                *p = 0;
            } else {
                *p = 1;
                if (*(unsigned char *)(self + 8) == func_02030788()) {
                    *(int *)((char *)p + 0x120) = 0;
                }
            }
            func_ov101_020bb738(self, (int)p);
        }
        break;
    }
    func_ov022_020a384c(self, mode);
    flag = 0;
    if (*(signed char *)(self + 0x2bb2) == 2) { flag = 1; }
    if (mode >= 0x2e) {
        ret = func_ov002_020519b0(mode, *(int *)(self + 0x6bc), *(int *)(self + 0xc));
        func_ov002_02052024((void *)(self + 0xf0c), base + 0x2c2c, mode, 2, ret);
        return;
    }
    func_ov002_020521a4((void *)(self + 0xf0c), base + 0x2c2c, mode, flag);
}
