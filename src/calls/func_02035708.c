extern char data_0204c500;
extern void func_020343cc(void *ptr);

void func_02035708(void) {
    register int index asm("r4") = 0;
    register char *ptr asm("r5") = &data_0204c500;
    register int zero asm("r6") = index;

    for (; index < 2; index++) {
        if (*(int *)(ptr + 0x44) != 0) {
            func_020343cc(ptr + 0x44);
            *(int *)(ptr + 0x44) = zero;
        }
        ptr += 0x48;
    }
}
