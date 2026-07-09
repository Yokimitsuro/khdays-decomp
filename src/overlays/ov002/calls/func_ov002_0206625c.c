extern int func_02030788();
extern int data_ov002_0207f9b0;

void func_ov002_0206625c(int arg0) {
    int r = func_02030788(arg0);
    *(unsigned short *)((char *)&data_ov002_0207f9b0 + r * 0x14) = 1;
}
