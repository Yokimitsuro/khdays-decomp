extern int func_01fffde0(int arg0);
int func_ov022_020886d0(int arg0) {
    int e = func_01fffde0(arg0);
    if (e != 0 && (*(unsigned int *)(e + 0x464) & 0x8000000) != 0) return 1;
    return 0;
}
