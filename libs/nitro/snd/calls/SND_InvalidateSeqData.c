/* Invalidates a sequence range: sound command 0x1e. */
extern void PushCommand_impl(int cmd, unsigned int start, unsigned int end, int a, int b);

void SND_InvalidateSeqData(unsigned int start, unsigned int end) {
    PushCommand_impl(0x1e, start, end, 0, 0);
}
