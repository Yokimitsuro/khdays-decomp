/* Call func_ov002_02066920(param_1, param_2) only when the global at
 * data_ov002_0207f9f0 is set. */
extern void func_ov002_02066920(int a, int b);
extern int data_ov002_0207f9f0;

void func_ov002_02066c9c(int param_1, int param_2) {
    if (*(int *)&data_ov002_0207f9f0 != 0) {
        func_ov002_02066920(param_1, param_2);
    }
}
