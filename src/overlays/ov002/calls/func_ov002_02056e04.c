extern int func_ov002_020573a4();
extern int func_ov002_0205d98c();
extern int data_ov002_0207f614;

void func_ov002_02056e04(int arg0) {
    if (*(int *)&data_ov002_0207f614 == 0) {
        return;
    }
    if (func_ov002_020573a4() == 0) {
        return;
    }
    func_ov002_0205d98c(arg0);
}
