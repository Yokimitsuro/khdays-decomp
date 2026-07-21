/* Handle a state-2 button: state 0 or 4 cancels (func_02050970 with -1); state 1 commits the
 * pending edit (dialog + apply, clear the three edit slots at +0x140 stride 8, reset state);
 * any other state just chirps. Always plays the confirm SFX.
 *
 * NON-MATCHING (equivalent), 8 bytes over. The whole dispatch (shared 0/4 case, case 1, the calls)
 * reproduces; only the 3-iteration clear loop ties: the ROM keeps the loop counter i live and
 * scales it inline (add r0, param_1, i lsl#3; str [r0,#0x140]), whereas mwcc 139 spins up a
 * separate induction variable (i*2 as an int index, or an i*8 running pointer). Same strength-
 * reduction tie as func_ov008_02054d3c/0208b148/0205ffe8/02054b18; no spelling suppresses it. */
extern int func_ov008_02050c54(void);
extern void func_ov008_02050970(int a, int b);
extern void func_ov008_02068d58(int a, int b);
extern void func_ov008_020693c4(int *obj, int a);
extern void func_02033b78(int a, int b);

void func_ov008_02068878(int *param_1) {
    func_ov008_02050c54();
    if (param_1[0x8f] != 0) {
        return;
    }
    switch (param_1[1]) {
    case 0:
    case 4:
        func_ov008_02050970(0, -1);
        break;
    case 1:
        func_ov008_02068d58(1, 0);
        func_ov008_020693c4(param_1, 0);
        {
            int i;
            for (i = 0; i < 3; i++) {
                param_1[i * 2 + 0x50] = 0;
            }
        }
        param_1[1] = 0;
        break;
    }
    func_02033b78(0, 3);
}
