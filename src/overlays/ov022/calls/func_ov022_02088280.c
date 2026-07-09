extern int func_01fffde0(int arg0);
void func_ov022_02088280(int arg0, short arg1) {
    int e = func_01fffde0(arg0);
    unsigned int *p;
    if (e == 0) return;
    p = *(unsigned int **)(e + 0x20);
    if ((*p & 0x20) != 0) return;
    *(short *)((char *)p + 0x80) = arg1 + 0x8000;
    *(unsigned short *)((char *)p + 4) |= 0x20;
}
