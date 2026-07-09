extern int func_ov025_02084afc();
extern int func_ov025_02084a7c();
extern void func_ov025_0209bfcc();
extern int data_ov025_020b4f6c;

void func_ov025_0209c00c(short *arg0, short arg1, int arg2) {
    func_ov025_02084afc();
    func_ov025_02084a7c();
    func_ov025_0209bfcc(arg0, *(short *)((char *)&data_ov025_020b4f6c + arg1 * 0x14 + arg2 * 4));
}
