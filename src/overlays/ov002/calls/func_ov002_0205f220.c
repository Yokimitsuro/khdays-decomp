/* If the pointer at *global is non-null, forward it (with param_1). */
extern void func_ov002_0205e79c(int arg, int ptr);
extern int data_ov002_0207f624;

void func_ov002_0205f220(int param_1) {
    int ptr = *(int *)&data_ov002_0207f624;
    if (ptr != 0) {
        func_ov002_0205e79c(param_1, ptr);
    }
}
