/* Sound command 0x6. */
extern void PushCommand_impl(int cmd, int a, int b, int c, int d);

void SNDi_SetPlayerParam(int a, int b, int c, int d) {
    PushCommand_impl(0x6, a, b, c, d);
}
