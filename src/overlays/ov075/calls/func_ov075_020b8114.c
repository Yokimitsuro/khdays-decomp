extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov075_020b8184(int a);
extern void func_ov075_020b985c(int a);
extern void func_ov075_020b9a7c(int a);
extern void func_ov075_020b877c(int a);
extern void func_ov022_020a4798(int a, int b, int c);
extern void func_ov022_0209fb24(void);
void *func_ov075_020b8114(int param) {
    int obj = NNSi_FndGetCurrentRootHeap();
    func_ov075_020b8184(param);
    func_ov075_020b985c(obj);
    func_ov075_020b9a7c(obj);
    func_ov075_020b877c(obj);
    func_ov022_020a4798(obj, 0x4c, 0xcc);
    return (void *)func_ov022_0209fb24;
}
