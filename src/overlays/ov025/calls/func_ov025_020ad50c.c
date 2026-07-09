extern int func_ov025_020acefc();
extern int func_ov025_020acfcc();

void func_ov025_020ad50c(int arg0) {
    if (*(int *)(arg0 + 0x158) != 0) {
        func_ov025_020acefc(arg0);
    }
    if (*(int *)(arg0 + 8) == 0) {
        return;
    }
    func_ov025_020acfcc(arg0);
}
