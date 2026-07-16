/* func_ov000_0204ef34 -- ov000 boot dispatcher. Ticks the scene (func_020352c0), then runs the
 * boot path selected by heap+0x4c31: 0 = cold boot (func_ov000_0204ee24), 1 = resume
 * (func_ov000_0204ede0); any other value falls through with the default -2. Always finishes with
 * func_ov000_02054f08. */
extern int  NNSi_FndGetCurrentRootHeap(void);
extern void func_020352c0(int heap);
extern int  func_ov000_0204ee24(void);
extern int  func_ov000_0204ede0(void);
extern void func_ov000_02054f08(void);

int func_ov000_0204ef34(void) {
    int result = -2;
    int heap = NNSi_FndGetCurrentRootHeap();
    func_020352c0(heap);
    switch (*(char *)(heap + 0x4c31)) {
    case 0:
        result = func_ov000_0204ee24();
        break;
    case 1:
        result = func_ov000_0204ede0();
        break;
    }
    func_ov000_02054f08();
    return result;
}
