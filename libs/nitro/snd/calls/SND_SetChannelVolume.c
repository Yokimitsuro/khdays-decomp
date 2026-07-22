/* Sound command 0x14. */
extern void PushCommand_impl(int cmd, int a, int b, int c, int d);

void SND_SetChannelVolume(int a, int b, int c) {
    PushCommand_impl(0x14, a, b, c, 0);
}
