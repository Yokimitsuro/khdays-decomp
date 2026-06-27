extern void func_0201c254(void *addr, int b, int c);
extern void SND_InvalidateBankData(const void *start, const void *end);
extern void func_02008f44(void *addr);

void func_0201c2d4(void *addr, int size, int b, int c) {
    func_0201c254(addr, b, c);
    SND_InvalidateBankData(addr, (char *)addr + size);
    func_02008f44(addr);
}
