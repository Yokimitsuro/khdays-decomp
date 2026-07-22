/* Invalidates a bank range: sound command 0x1f. */
extern void PushCommand_impl(int cmd, unsigned int start, unsigned int end, int a, int b);

void SND_InvalidateBankData(unsigned int start, unsigned int end) {
    PushCommand_impl(0x1f, start, end, 0, 0);
}
