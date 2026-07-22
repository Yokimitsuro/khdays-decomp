/* func_ov022_020aeef8 -- look up the state slot for (byte@arg0+9 - 1), release it from state 9
 * to state 1, run func_ov022_020aef50 with a 3-word scratch, and put the slot back to 9 when the
 * call reports work done. Returns that same result.
 *
 * Parked as a "1-register colouring tie": the ROM materialises the constant 9 in r1
 * (`movne r1,#9 ; strne r1,[r4]`) and keeps the call's result in r0, while mwcc reuses r0 for the
 * constant. r0 is not free -- the function RETURNS the result, so it has to survive to the `pop`.
 * Declared `void`, no body rewrite could ever have produced r1. Same lever as func_ov010_0204cac0:
 * when the residue is "which register holds a dead-looking value", ask whether the value is the
 * return value first.
 */
extern int *func_020358a4(int arg0);
extern int func_ov022_020aef50(int arg0, int arg1, unsigned int *arg2);

int func_ov022_020aeef8(int arg0, int arg1, int arg2, int arg3) {
    unsigned int buf[3];
    int *p = func_020358a4((*(unsigned char *)(arg0 + 9) - 1) & 0xff);
    int r;
    if (*p == 9) *p = 1;
    r = func_ov022_020aef50(arg0, arg1, buf);
    if (r != 0) *p = 9;
    return r;
}
