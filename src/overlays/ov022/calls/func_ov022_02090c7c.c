extern void func_0202a634(unsigned short *arg0, unsigned int *arg1, int arg2, int arg3);

void func_ov022_02090c7c(unsigned char *arg0, int arg1, unsigned int *arg2, unsigned char arg3) {
    func_0202a634((unsigned short *)(arg0 + 0x28), arg2, 1, arg1 + 7);
    arg0[1] = arg3;
    arg0[2] = 0;
    *(int *)(arg0 + 4) = 0;
    arg0[8] = 0xff;
    *(int *)(arg0 + 0x138) = 0;
    *(int *)(arg0 + 0x130) = 0;
    arg0[0] = 0;
}
