/* Bind param_2 to the two sub-objects at (param_1)+0x5cc[0..1] and the one at +0x5d4,
 * then run the ov107 attach for the pair. */
extern void func_ov107_020c2b38(int a, int b);
extern void func_ov107_020c7c1c(int a, int b);
void func_ov212_020ccca8(int param_1, int param_2) {
    int i;
    for (i = 0; i < 2; i++) {
        func_ov107_020c2b38(param_2, ((int *)param_1)[i + 0x173]);
    }
    func_ov107_020c2b38(param_2, *(int *)(param_1 + 0x5d4));
    func_ov107_020c7c1c(param_1, param_2);
}
