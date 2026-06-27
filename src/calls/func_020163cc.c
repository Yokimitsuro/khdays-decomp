extern void G3X_Init(void);
extern void func_02015630(void);

void func_020163cc(void) {
    G3X_Init();
    func_02015630();
    *(volatile unsigned int *)0x04000600 = (*(volatile unsigned int *)0x04000600 & ~0xc0000000u) | 0x80000000u;
}
