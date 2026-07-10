extern int func_01fffe14(void);
extern void func_ov022_020884ec(unsigned int arg0);
extern void func_ov022_02086638(int arg0, int arg1);
extern void func_ov022_02083c08(int arg0);
extern void func_020340d0(int arg0);
extern void func_ov002_0205193c(void);
extern int data_ov022_020b2e60;
extern void func_ov022_02083878(void);

int func_ov022_02083844(void) {
    func_ov022_020884ec(func_01fffe14());
    func_ov022_02086638(*(int *)(*(int *)&data_ov022_020b2e60 + 8), 1);
    func_ov022_02083c08(1);
    func_020340d0(1);
    func_ov002_0205193c();
    return (int)func_ov022_02083878;
}
