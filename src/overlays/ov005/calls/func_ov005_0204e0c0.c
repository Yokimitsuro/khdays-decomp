/* Chain func_ov005_0204e0d0(param_1, param_2) into func_ov005_0204e0b8 with param_3. */
extern int func_ov005_0204e0d0(int a, int b);
extern void func_ov005_0204e0b8(int a, int b);
void func_ov005_0204e0c0(int param_1, int param_2, int param_3) {
    func_ov005_0204e0b8(func_ov005_0204e0d0(param_1, param_2), param_3);
}
