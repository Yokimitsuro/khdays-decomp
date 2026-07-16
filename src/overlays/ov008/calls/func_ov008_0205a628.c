/* func_ov008_0205a628 -- tear down an ov008 menu object: release its two renderers
 * (obj+0x4f4, obj+0x51c), free each live text buffer (obj+0x1b8 / obj+0x31c, gated by
 * obj+0x140 / obj+0x144), release the base node (obj+0x38) and run the final cleanup. */
extern void func_02011134(int p);
extern void func_02011320(int p);
extern void func_ov008_02059dd8(int p);
extern void func_0202a7dc(int p);
extern void func_ov008_0205a1c4(int obj);

void func_ov008_0205a628(int param_1) {
    func_02011134(param_1 + 0x4f4);
    func_02011320(param_1 + 0x51c);
    if (*(int *)(param_1 + 0x140) != 0) {
        func_ov008_02059dd8(param_1 + 0x1b8);
    }
    if (*(int *)(param_1 + 0x144) != 0) {
        func_ov008_02059dd8(param_1 + 0x31c);
    }
    func_0202a7dc(param_1 + 0x38);
    func_ov008_0205a1c4(param_1);
}
