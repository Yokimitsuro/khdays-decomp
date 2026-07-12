/* Build the base object, then attach four sub-objects at +0x88..+0x94. */
extern int func_ov025_0208843c(int self, int arg);
void func_ov025_02087880(int param_1, int param_2) {
    int obj = func_ov025_0208843c(param_1, *(int *)param_2);
    *(int *)(obj + 0x88) = func_ov025_0208843c(param_1, *(int *)(param_2 + 0x40));
    *(int *)(obj + 0x8c) = func_ov025_0208843c(param_1, *(int *)(param_2 + 0x44));
    *(int *)(obj + 0x90) = func_ov025_0208843c(param_1, *(int *)(param_2 + 0x48));
    *(int *)(obj + 0x94) = func_ov025_0208843c(param_1, *(int *)(param_2 + 0x4c));
}
