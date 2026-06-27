extern void func_0201c254(void *addr, int b, int c);
extern void SND_InvalidateWaveData(const void *start, const void *end);
extern void SND_DestroyWaveArc(void *wa);

void func_0201c304(void *addr, int size, int b, int c) {
    func_0201c254(addr, b, c);
    SND_InvalidateWaveData(addr, (char *)addr + size);
    SND_DestroyWaveArc(addr);
}
