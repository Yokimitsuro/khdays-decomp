extern int func_01fffde0(int arg0);
unsigned short func_ov022_02088254(int arg0) {
    int e = func_01fffde0(arg0);
    if (e != 0) return *(unsigned short *)(*(int *)(e + 0x20) + 0x80) - 0x8000;
    return 0;
}
