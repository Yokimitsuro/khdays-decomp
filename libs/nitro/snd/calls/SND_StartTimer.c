/* Sound command 0xc. */
extern void PushCommand_impl(int cmd, int a, int b, int c, int d);

void SND_StartTimer(int a, int b, int c, int d) {
    PushCommand_impl(0xc, a, b, c, d);
}
