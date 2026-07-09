struct e16 { unsigned short tag; unsigned char pad[14]; };

int func_ov025_0208ffc4(int arg0, unsigned int arg1) {
    int i;
    if ((int)arg1 > 0) arg1 = arg1 - 1;
    i = 0;
    do {
        if (arg1 == ((struct e16 *)arg0)[i + 57].tag)
            return arg0 + 0x390 + i * 0x10;
        i++;
    } while (i < 0xd1);
    return 0;
}
