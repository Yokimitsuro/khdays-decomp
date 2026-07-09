extern int func_ov002_020527e8();
extern int data_ov002_0207f624;

void func_ov002_0205f56c(void) {
    int p = *(int *)&data_ov002_0207f624;
    if (*(int *)(p + 0x660) == 0) {
        return;
    }
    func_ov002_020527e8(p + 0xc);
}
