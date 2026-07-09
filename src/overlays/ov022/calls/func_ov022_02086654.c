extern int func_ov022_02083f5c(void);
extern void func_ov022_02086748(unsigned char *arg0, int arg1);
int func_ov022_02086654(unsigned char *arg0) {
    int e = func_ov022_02083f5c();
    if (*(int *)(e + 0x20) != 0) {
        func_ov022_02086748(arg0, *(int *)(e + 0x20) + 4);
        return 1;
    }
    *arg0 = 0;
    return 0;
}
