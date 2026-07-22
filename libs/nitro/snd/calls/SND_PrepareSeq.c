/* Sound command 0x2. */
extern void PushCommand_impl(int cmd, int a, int b, int c, int d);

void SND_PrepareSeq(int a, int b, int c, int d) {
    PushCommand_impl(0x2, a, b, c, d);
}
