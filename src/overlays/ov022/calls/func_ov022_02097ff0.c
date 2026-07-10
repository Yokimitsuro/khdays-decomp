struct field4e8 { unsigned char b0 : 1; unsigned char b1 : 1; unsigned char b2 : 1; unsigned char b3 : 1; unsigned char b4 : 1; unsigned char rest : 3; };

void func_ov022_02097ff0(int arg0) {
    *(unsigned char *)(arg0 + 0x4d0) = 7;
    *(unsigned short *)(arg0 + 0x4d2) = 0;
    ((struct field4e8 *)(arg0 + 0x4e8))->b1 = 0;
    *(unsigned char *)(arg0 + 0x4d6) = 7;
    *(unsigned short *)(arg0 + 0x4d8) = 0;
    ((struct field4e8 *)(arg0 + 0x4e8))->b2 = 0;
    ((struct field4e8 *)(arg0 + 0x4e8))->b4 = 0;
    *(unsigned short *)(arg0 + 0x4e4) = (unsigned short)0xffff;
}
