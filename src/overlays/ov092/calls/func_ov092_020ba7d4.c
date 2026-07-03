extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov092_020ba844(int a);
extern void func_ov092_020bbf1c(int a);
extern void func_ov092_020bc13c(int a);
extern void func_ov092_020bae3c(int a);
extern void func_ov022_020a4798(int a, int b, int c);
extern void func_ov022_0209fb24(void);
void *func_ov092_020ba7d4(int param) {
    int obj = NNSi_FndGetCurrentRootHeap();
    func_ov092_020ba844(param);
    func_ov092_020bbf1c(obj);
    func_ov092_020bc13c(obj);
    func_ov092_020bae3c(obj);
    func_ov022_020a4798(obj, 0x4c, 0xcc);
    return (void *)func_ov022_0209fb24;
}
