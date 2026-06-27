extern void OS_DisableIrqMask();

extern struct {
    unsigned short state;
    unsigned short pad;
    int field_4;
    int field_8;
    int field_c;
    int field_10;
} data_02044680;

void func_020037a0(void) {
    if (data_02044680.state != 0) return;
    data_02044680.state = 1;
    data_02044680.field_c = 0;
    data_02044680.field_10 = 0;
    OS_DisableIrqMask(4);
    data_02044680.field_8 = 0;
    data_02044680.field_4 = 0;
}
