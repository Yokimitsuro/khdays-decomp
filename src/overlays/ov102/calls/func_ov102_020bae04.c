extern void func_0202a634(int a, int b, int c, int d);
extern void func_ov102_020bafdc(int p);
extern int data_ov102_020bb920;
extern int data_ov102_020bb8e0;

void func_ov102_020bae04(void) {
    int d = data_ov102_020bb920;
    char *a = (char *)(d + 0x2000);
    char *b = (char *)(d + 0x2c50);
    *(int *)(a + 0xc50) = 0;
    *(int *)(b + 0x10) = 0;
    func_0202a634((int)(b + 0x14), (int)&data_ov102_020bb8e0, 1, *(unsigned char *)(d + 9) + 7);
    func_ov102_020bafdc(d);
}
