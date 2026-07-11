extern void func_ov002_0206e700(int a, int b);
extern int data_0204be18;

int func_ov069_020b847c(unsigned int arg) {
    func_ov002_0206e700(1, *(unsigned short *)(*(char **)&data_0204be18 + 0x196c));
    if (*(unsigned short *)(*(char **)&data_0204be18 + 0x196c) < arg) {
        return 0;
    }
    return 1;
}
