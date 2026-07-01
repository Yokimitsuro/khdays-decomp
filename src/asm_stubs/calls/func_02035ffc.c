extern long long func_020031d4(void);

void func_02035ffc(int *ptr) {
    long long value = func_020031d4();

    ptr[4] = (int)value;
    ptr[5] = (int)(value >> 32);
    __asm
    {
        ldr r0, [ptr, #0x18]
        bic r0, r0, #0x1
        orr r1, r0, #0x1
        bic r0, r1, #0x2
        bic r0, r0, #0x4
        str r0, [ptr, #0x18]
    }
}
