extern void MI_CpuFill8(void *dst, int value, int size);
extern void NNS_FndInitList(void *list, int objectSize);
extern void func_ov002_0205280c(void *this_, void *vtable);
extern int func_0201ef9c(int arg0, int arg1);
extern void func_ov302_020cc598(int this_, int arg1, int arg2);
extern void data_ov302_020cc740(void);

void func_ov302_020cc64c(int this_, int *init) {
    MI_CpuFill8((void *)this_, 0, 0x24);
    NNS_FndInitList((void *)(this_ + 0x18), 0x4c);
    func_ov002_0205280c((void *)this_, data_ov302_020cc740);
    *(int *)(this_ + 0xc) = init[2];
    *(int *)(this_ + 0x14) = func_0201ef9c(init[0], 0xe);
    func_ov302_020cc598(this_, init[2], init[1]);
}
