extern int func_01fffe14();
extern int func_01fffde0();
extern int data_ov002_0207e768;

int func_ov002_02050b68(int arg0) {
    func_01fffe14(arg0);
    func_01fffde0();
    return *(int *)((char *)&data_ov002_0207e768 + arg0 * 0xc);
}
