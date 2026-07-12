/* Bind param_2 to the two sub-objects at (param_1)+0x5cc[0..1] and the one at +0x5d4,
 * then run the ov107 attach for the pair. */
extern void func_ov107_020c2b20(int a, int b);
extern void func_ov107_020c7b70(int a, int b);
void func_ov212_020ccc60(int param_1, int param_2) {
    int i;
    for (i = 0; i < 2; i++) {
        func_ov107_020c2b20(param_2, ((int *)param_1)[i + 0x173]);
    }
    func_ov107_020c2b20(param_2, *(int *)(param_1 + 0x5d4));
    func_ov107_020c7b70(param_1, param_2);
}
