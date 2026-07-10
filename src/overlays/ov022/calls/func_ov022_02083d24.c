extern unsigned char func_ov002_0206da10(void);
extern void func_ov002_0206d9fc(int arg0);
extern int data_ov022_020b2e60;

void func_ov022_02083d24(void) {
    int *g = &data_ov022_020b2e60;
    *(unsigned short *)*g &= ~2;
    *(unsigned char *)(*g + 0x3e) = func_ov002_0206da10();
    func_ov002_0206d9fc(0);
    *(int *)(*g + 4) = 4;
}
