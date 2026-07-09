extern int data_0204c4d8;
extern int func_ov002_0206d384();

int func_ov002_020693cc(void) {
    *(int *)((char *)&data_0204c4d8 + 0x14) = 0;
    return func_ov002_0206d384(&data_0204c4d8);
}
