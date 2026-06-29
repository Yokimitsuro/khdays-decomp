extern void func_0202ea48(void *ptr);
extern void func_0202f4a4(void *ptr1, void *ptr2);

void func_0203c9ec(unsigned char *ptr) {
    func_0202ea48(ptr);
    func_0202f4a4(ptr, ptr);
    ptr[0x28] &= ~1;
}
