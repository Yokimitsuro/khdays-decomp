extern int func_02011390();
extern int func_02011358();

int func_02011558(int this_) {
    if (func_02011390(this_) != 0) return 0;
    *(unsigned short *)(this_ + 8) = func_02011358(this_, *(unsigned short *)(this_ + 8));
    *(unsigned short *)(this_ + 0xc) -= 1;
    return 1;
}
