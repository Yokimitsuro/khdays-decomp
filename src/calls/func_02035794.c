extern void func_020358c0();
extern char data_0204c678[];
void func_02035794(int param_1, int param_2, unsigned int param_3, unsigned char *param_4)
{
    unsigned char *row = (unsigned char *)(data_0204c678 + param_1 * 0x104 + 0x9c) + param_2 * 2;
    unsigned char b;
    row[0] = param_4[0];
    b = param_4[1];
    row[1] = b;
    if (row[0] > b)
        row[0] = b;
    func_020358c0(param_1, param_2 + 1, param_3);
}
