/* func_ov005_02050cec -- build, hand over and tear down one transient layout pass.
 * Everything lives on the stack: an NNSFndList threaded at offset 0x28, a 0x100-byte state block
 * and a 0x1e0-byte work area. The state is initialised, populated from `arg`, resolved, handed to
 * func_02035a58 for the caller's object, post-processed, and released again before returning --
 * nothing survives the call. */
extern void NNS_FndInitList(void *list, int offset);
extern void func_ov005_020506a4(void *state, int v);
extern void func_ov005_020509ac(void *state, void *work, void *list, int arg);
extern void func_ov005_02050730(void *state, void *work, void *list);
extern void func_02035a58(int obj, void *state);
extern void func_ov005_02050bfc(void *state, void *work, void *list);
extern void WM_EndKeySharing_0x02050724(void *state);

void func_ov005_02050cec(int obj, int arg) {
    char list[0xc];
    char work[0x1e0];
    char state[0x100];

    NNS_FndInitList(list, 0x28);
    func_ov005_020506a4(state, 0);
    func_ov005_020509ac(state, work, list, arg);
    func_ov005_02050730(state, work, list);
    func_02035a58(obj, state);
    func_ov005_02050bfc(state, work, list);
    WM_EndKeySharing_0x02050724(state);
}
