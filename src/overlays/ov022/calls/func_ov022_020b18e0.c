extern void func_ov022_020b152c();
void func_ov022_020b18e0(unsigned int *arg0) {
    if ((*(unsigned char *)((int)arg0 + 9) & 2) != 0 || (*(unsigned char *)((int)arg0 + 9) & 1) != 0)
        func_ov022_020b152c((unsigned char *)*arg0);
}
