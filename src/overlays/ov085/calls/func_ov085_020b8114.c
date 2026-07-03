extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov085_020b815c(int a);
extern void func_ov085_020b8744(int a);
extern void func_ov022_020a4798(int a, int b, int c);
extern void func_ov022_0209fb24(void);
void *func_ov085_020b8114(int param) {
    int obj = NNSi_FndGetCurrentRootHeap();
    func_ov085_020b815c(param);
    func_ov085_020b8744(obj);
    func_ov022_020a4798(obj, 0x52, 0xd4);
    return (void *)func_ov022_0209fb24;
}
