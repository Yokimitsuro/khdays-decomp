/* Tail-call func_ov008_0205a890 on the sub-object at param_1+0x1414, passing
 * WM_EndKeySharing as the teardown callback. */
extern int func_ov008_0205a890(int obj, int callback);
extern void WM_EndKeySharing_0x0205697c(void);

int func_ov008_0205a8c4(int param_1) {
    return func_ov008_0205a890(param_1 + 0x1414, (int)&WM_EndKeySharing_0x0205697c);
}
