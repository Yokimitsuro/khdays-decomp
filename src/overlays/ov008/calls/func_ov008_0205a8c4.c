/* Tail-call WM_EndKeySharing on the sub-object at param_1+0x1414, passing
 * func_ov008_0205a890 as the teardown callback.
 *
 * The branch target is the pool word loaded into r12, which the original fills
 * with 0x0205697c; func_ov008_0205a890 is the second pool word and arrives in r1
 * as the callback argument. */
extern int WM_EndKeySharing_0x0205697c(int obj, int callback);
extern void func_ov008_0205a890(void);

int func_ov008_0205a8c4(int param_1) {
    return WM_EndKeySharing_0x0205697c(param_1 + 0x1414, (int)&func_ov008_0205a890);
}
