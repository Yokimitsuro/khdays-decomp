extern void func_ov022_02083c08(int a);
extern unsigned long long func_020031d4(void);
extern void func_ov022_02083b20(void);
extern int data_0204be04;
extern int data_ov022_020b2e60;

int func_ov022_02083aac(void) {
    int g = data_ov022_020b2e60;
    int r = 0;
    if (*(unsigned char *)&data_0204be04 != 0) return r;
    func_ov022_02083c08(1);
    if (*(unsigned long long *)(g + 0x24) + 0x17f898 <= func_020031d4()) {
        *(int *)(g + 0x1c) = 0;
        r = (int)func_ov022_02083b20;
        *(int *)(g + 0x20) = 0;
    }
    return r;
}
