extern int data_ov002_0207f614;
extern int func_ov002_020636c0();

int func_ov002_020574e4(int arg0) {
    *(int *)(*(int *)&data_ov002_0207f614 + 0x1b8) = arg0;
    return func_ov002_020636c0(arg0);
}
