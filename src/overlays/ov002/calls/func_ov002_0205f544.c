extern int func_ov002_02052794();
extern int data_ov002_0207f624;

void func_ov002_0205f544(void) {
    int p = *(int *)&data_ov002_0207f624;
    if (*(int *)(p + 0x660) == 0) {
        return;
    }
    func_ov002_02052794(p + 0xc);
}
