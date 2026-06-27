extern void func_0201c254(void *a, int b, int c);
extern void SND_DestroyWaveArc(void *wa);

void func_0201c334(void *wa, int unused, int b, int c) {
    func_0201c254(wa, b, c);
    SND_DestroyWaveArc(wa);
}
