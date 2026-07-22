/* Sound command 0x9. */
extern void PushCommand_impl(int cmd, int a, int b, int c, int d);

void SND_SetTrackAllocatableChannel(int a, int b, int c) {
    PushCommand_impl(0x9, a, b, c, 0);
}
