extern void func_ov011_0205cad8();
extern int data_ov011_0205e960;
extern void func_0203256c();

void func_ov011_0205c370(void) {
    int r1;
    func_ov011_0205cad8();
    r1 = *(int *)((char *)&data_ov011_0205e960 + 4);
    if (*(int *)(r1 + 4) != 3) return;
    func_0203256c(r1 + 0x28508);
}
