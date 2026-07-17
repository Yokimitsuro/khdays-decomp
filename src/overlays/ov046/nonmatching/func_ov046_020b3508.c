/*
 * func_ov046_020b3508 -- UNFINISHED. 316 vs 292 (6 instructions over).
 * x4 family -> worth 4. The C below is semantically complete and verified against both the
 * disassembly and Ghidra; what is missing is one mwcc trick, described below.
 *
 * WHAT IT DOES: switch the actor's mode (mode - 0x2e selects the arm; each arm no-ops if
 * the mode did not change, +0x6bc caches it). 0x2e re-inits; 0x2f rebinds the block at
 * base+0x2c80; 0x30/0x31 set that block's flag word to 0/1 -- and for 0x31 only, if the
 * actor's slot byte (+8) equals the current owner (02030788), clear base+0x2da0 -- then
 * re-arm via 020b4198. Afterwards hand the mode down (020a384c) and forward it to the UI:
 * below 0x2e straight through (020521a4), otherwise translated first (020519b0 -> 02052024).
 *
 * ★ THE FINDING, and it is the whole gap: the ROM's `push {r3, r4, r5, r6, r7, lr}` does TWO
 * jobs at once. Pushing r3 homes param_4, AND the slot it lands in is [sp+0] -- which is
 * exactly where a 5-argument call must place arg5. So `020521a4(..., param_4)` needs no
 * setup at all: the value is already in the right place, put there by the prologue.
 *      ROM:   push {r3,...}                      (param_4 homed AND arg5 placed)
 *      mine:  push {r3,...} ; sub sp,#4 ; mov r6,r3 ; ... ; str r6,[sp]
 * mwcc gave param_4 a callee-saved register (it is live across 020a384c and 02030788) and
 * then allocated a FRESH outgoing slot for it -- 6 instructions and an extra pushed
 * register. Both are correct; only one is free.
 *
 * This is the same family of observation as the push-list rule in codegen-cracks.md ("read
 * the push list as a fact about live ranges"): here the push list is telling you that the
 * ROM keeps param_4 in MEMORY from the first instruction, never in a register.
 *
 * NEXT STEP: find the source form that makes mwcc home param_4 to the stack instead of
 * promoting it to r6. Not yet tried: making the 020521a4 call the ONLY thing that mentions
 * p4 in a way mwcc can see early (it already is), or restructuring so p4 is not live across
 * the two intervening calls. If mwcc simply will not do it from clean C, that is worth
 * knowing explicitly -- but check the arity of 020521a4 and 02052024 against the tree
 * first: both are called here with FIVE arguments and the tree has a documented history of
 * this exact function (020551a4) being mis-declared with four.
 */
extern int data_ov046_020b4b40;

extern void WM_EndKeySharing_0x020b3a70(int self);
extern void func_ov046_020b4184(int self, int p);
extern unsigned short func_02030788(void);
extern void func_ov046_020b4198(int self, int p);
extern void func_ov022_020a384c(int self, int mode);
extern int func_ov002_020519b0(int a, int b, int c);
extern void func_ov002_02052024(void *a, int b, int c, int d, int e);
extern void func_ov002_020521a4(void *a, int b, int c, int d, int e);

void func_ov046_020b3508(int self, int mode, int p3, int p4) {
    int base = data_ov046_020b4b40;
    int *p = (int *)(base + 0x2c80);
    int flag;
    int ret;

    switch (mode - 0x2e) {
    case 0:
        if (*(int *)(self + 0x6bc) != mode) {
            WM_EndKeySharing_0x020b3a70(self);
        }
        break;
    case 1:
        if (*(int *)(self + 0x6bc) != mode) {
            func_ov046_020b4184(self, (int)p);
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
                    *(int *)(base + 0x2da0) = 0;
                }
            }
            func_ov046_020b4198(self, (int)p);
        }
        break;
    }
    func_ov022_020a384c(self, mode);
    flag = (*(signed char *)(self + 0x2bb2) == 2);
    if (mode < 0x2e) {
        func_ov002_020521a4((void *)(self + 0xf0c), base + 0x2c2c, mode, flag, p4);
        return;
    }
    ret = func_ov002_020519b0(mode, *(int *)(self + 0x6bc), *(int *)(self + 0xc));
    func_ov002_02052024((void *)(self + 0xf0c), base + 0x2c2c, mode, 2, ret);
}
