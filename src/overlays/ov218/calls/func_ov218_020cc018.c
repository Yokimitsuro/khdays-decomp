/* Back-link param_1 into the sub-object (+0x4c), then arm it via func_02014e18
 * (handler func_ov218_020cbfc4, mode 0/6/3). */
extern void func_02014e18(int a, int b, int c, int d, int e);
extern void func_ov218_020cbfc4(void);
void func_ov218_020cc018(int param_1) {
    *(int *)(*(int *)(*(int *)(param_1 + 0x384) + 0x88) + 0x4c) = param_1;
    func_02014e18(*(int *)(*(int *)(param_1 + 0x384) + 0x88) + 0x20,
                  (int)&func_ov218_020cbfc4, 0, 6, 3);
}
