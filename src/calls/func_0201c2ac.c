extern void func_0201c254(void *addr, int b, int c);
extern void SND_InvalidateSeqData(const void *start, const void *end);

void func_0201c2ac(void *addr, int size, int b, int c) {
    func_0201c254(addr, b, c);
    SND_InvalidateSeqData(addr, (char *)addr + size);
}
