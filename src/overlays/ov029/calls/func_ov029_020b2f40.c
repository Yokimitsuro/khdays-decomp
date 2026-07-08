extern void func_0201e4a8();
extern int data_ov029_020b3200[];
void func_ov029_020b2f40(int param_1)
{
    int i;
    int *p;
    func_0201e4a8(0, param_1);
    p = data_ov029_020b3200;
    for (i = 0; i < 4; i++) {
        if (param_1 == *p) {
            data_ov029_020b3200[i] = -1;
            return;
        }
        p++;
    }
}
