extern int FX_Inv(int arg0, int arg1);
extern int data_0204c058;

int func_ov022_02094678(int arg0, unsigned int arg1) {
    unsigned char c = *(unsigned char *)&data_0204c058;
    int r;
    int x;
    switch (c) {
    case 0:
        r = 0x96;
        break;
    case 1:
        r = 100;
        break;
    case 2:
        r = 0x96;
        break;
    default:
        r = 0x96;
        break;
    }
    if (arg1 <= 1) {
        x = 0x1000;
    } else {
        x = 0x1000 - FX_Inv(arg0 << 0xc, arg1 << 0xc);
    }
    return r * x;
}
