extern int NNSi_FndGetCurrentRootHeap(void);
extern int func_01fffe14(void);
extern int func_ov022_02088474(unsigned int arg0);
extern void func_ov002_02071de4(int arg0);
extern void func_ov022_02083c08(int arg0);
extern int data_0204be04;
extern void func_ov022_02082c90(void);

int func_ov022_02082c54(void) {
    int h = NNSi_FndGetCurrentRootHeap();
    if (*(unsigned char *)&data_0204be04 != 0) return 0;
    *(char *)(h + 0x3d) = (char)func_ov022_02088474(func_01fffe14());
    func_ov002_02071de4(*(char *)(h + 0x3d));
    func_ov022_02083c08(0);
    return (int)func_ov022_02082c90;
}
