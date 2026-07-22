/* Invalidates a wave range: sound command 0x20. */
extern void PushCommand_impl(int cmd, unsigned int start, unsigned int end, int a, int b);

void SND_InvalidateWaveData(unsigned int start, unsigned int end) {
    PushCommand_impl(0x20, start, end, 0, 0);
}
