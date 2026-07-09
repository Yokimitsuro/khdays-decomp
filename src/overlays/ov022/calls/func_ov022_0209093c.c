extern int func_ov022_0209029c(short *arg0, unsigned int arg1);
extern int data_ov022_020b2a98;
void func_ov022_0209093c(short *arg0, int arg1, unsigned int arg2) {
    if (func_ov022_0209029c(arg0, 0xffffffff)) {
        unsigned int idx = *(unsigned int *)(arg0 + 6);
        if (idx != 0xffffffff) {
            ((void (**)(short *))&data_ov022_020b2a98)[idx](arg0);
        }
    }
}
