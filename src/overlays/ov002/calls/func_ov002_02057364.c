extern int func_ov002_0205f3f4();
extern int func_ov002_020573a4();
extern int data_ov002_0207f614;

void func_ov002_02057364(int arg0) {
    func_ov002_0205f3f4(arg0);
    if (func_ov002_020573a4() != 0) {
        return;
    }
    *(int *)(*(int *)&data_ov002_0207f614 + 0x18c) = 0;
}
