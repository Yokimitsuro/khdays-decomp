extern struct { int a, b; } data_0204a2fc;

void SND_ClearChannelBit(int bit) {
    data_0204a2fc.b &= ~(1 << bit);
}
