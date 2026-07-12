/* Build the base object, then attach four sub-objects at +0x88..+0x94. */
extern int func_ov005_0204e0d0(int self, int arg);
void func_ov005_0204d554(int param_1, int param_2) {
    int obj = func_ov005_0204e0d0(param_1, *(int *)param_2);
    *(int *)(obj + 0x88) = func_ov005_0204e0d0(param_1, *(int *)(param_2 + 0x40));
    *(int *)(obj + 0x8c) = func_ov005_0204e0d0(param_1, *(int *)(param_2 + 0x44));
    *(int *)(obj + 0x90) = func_ov005_0204e0d0(param_1, *(int *)(param_2 + 0x48));
    *(int *)(obj + 0x94) = func_ov005_0204e0d0(param_1, *(int *)(param_2 + 0x4c));
}
