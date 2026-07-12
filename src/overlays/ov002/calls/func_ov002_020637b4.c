/* If the pointer at (*global slot)+4 is non-null, forward it (with param_1). */
extern void func_0201e3cc(int arg, int ptr);
extern int data_ov002_0207f62c;

void func_ov002_020637b4(int param_1) {
    int ptr = *(int *)((char *)&data_ov002_0207f62c + 4);
    if (ptr != 0) {
        func_0201e3cc(param_1, ptr);
    }
}
