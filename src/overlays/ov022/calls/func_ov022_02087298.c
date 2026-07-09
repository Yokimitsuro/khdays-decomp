extern int func_01fffde0(int arg0);
extern void func_0202beb8(int arg0, int arg1);
extern void SNDi_ProcessEntryAlt(int arg0);
void func_ov022_02087298(int arg0) {
    int e = func_01fffde0(arg0);
    char c;
    if (e == 0) return;
    c = *(char *)(e + 0x4bc);
    func_0202beb8(c, 0);
    SNDi_ProcessEntryAlt(c);
    *(short *)(e + 0x66) = -1;
}
