extern void *SND_GetWaveDataAddress(int player, int channel);
extern void SND_SetWaveDataAddress(int player, int channel, void *addr);
extern void SND_InvalidateWaveData(const void *start, const void *end);

void func_0201c354(void *addr, int size, int player, int channel) {
    if (addr == SND_GetWaveDataAddress(player, channel))
        SND_SetWaveDataAddress(player, channel, 0);
    SND_InvalidateWaveData(addr, (char *)addr + size);
}
