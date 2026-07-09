extern int func_ov025_02084b14();
extern int data_ov025_020b575c;

int func_ov025_020a4d70(int arg0) {
    int x = func_ov025_02084b14(arg0);
    return data_ov025_020b575c != 0 ? *(int *)(x + 8) : 0;
}
