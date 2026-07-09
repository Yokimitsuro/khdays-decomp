void func_02024148(int arg0, int arg1, int arg2, int arg3, int arg4) {
    *(unsigned short *)0x0400000a = *(unsigned short *)0x0400000a & 0x43
        | (arg0 << 0xe) | (arg1 << 7) | (arg2 << 8) | (arg3 << 2) | (arg4 << 0xd);
}
