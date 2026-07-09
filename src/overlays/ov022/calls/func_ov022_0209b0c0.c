extern void func_01fff774(unsigned short *arg0, int arg1, int arg2);
void func_ov022_0209b0c0(int arg0, int arg1, int arg2) {
    unsigned int i = 0;
    do {
        func_01fff774((unsigned short *)(arg0 + 0x278c + arg1 * 0x108), i & 0xffff, arg2);
        i++;
    } while ((int)i < 5);
}
