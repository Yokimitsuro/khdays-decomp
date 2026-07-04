extern unsigned short *func_02012880(void *table, int a, int b);
extern void func_02012b98(int a, int b, int c, int d, int e);
extern int data_02041a54[];

void func_02012d24(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6) {
    unsigned short *row = func_02012880(data_02041a54, param_3, param_4);
    func_02012b98(param_1, row[2], param_2, param_5, param_6);
}
