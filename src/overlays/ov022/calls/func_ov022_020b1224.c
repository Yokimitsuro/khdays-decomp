extern int func_0201eea8(int arg0);
extern void func_ov022_020b1264(int arg0, int arg1);
extern void func_ov022_020b1290(int arg0, unsigned int *arg1);
int func_ov022_020b1224(int arg0) {
    if (func_0201eea8(*(int *)(arg0 + 0x2c))) {
        *(short *)(arg0 + 0x34) = 0;
        func_ov022_020b1264(arg0, 0);
        func_ov022_020b1290(arg0, (unsigned int *)(arg0 + 4));
        return 1;
    }
    return 0;
}
