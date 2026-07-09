extern int data_020427f0;
extern void func_02025464(int *arg0, int arg1, int *arg2, int arg3);
void func_ov022_020b1264(int arg0, int arg1, int arg2, int arg3) {
    int *p = &data_020427f0;
    int saved = *p;
    *p = 1;
    func_02025464(*(int **)(arg0 + 0x2c), 1, p, arg3);
    *p = saved;
}
