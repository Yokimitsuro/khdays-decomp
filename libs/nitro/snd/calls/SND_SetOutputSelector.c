/* Sound command 0x19. */
extern void PushCommand_impl(int cmd, int a, int b, int c, int d);

void SND_SetOutputSelector(int a, int b, int c, int d) {
    PushCommand_impl(0x19, a, b, c, d);
}
