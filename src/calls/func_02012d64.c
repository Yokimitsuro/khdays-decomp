extern unsigned short *func_02012880(void *table, int a, int b);
extern void func_02012c2c(int a, int b, int c, int d, int e);
extern int data_02041a3c[];
extern int data_02047390;

void func_02012d64(int param_1, int param_2, int param_3, int param_4, int param_5) {
    unsigned short *row = func_02012880(data_02041a3c, param_2, param_3);
    func_02012c2c(param_1, row[2], data_02047390, param_4, param_5);
}
