/* Sound command 7; the immediate flag rides in the top byte of the track mask. */
extern void PushCommand_impl(int cmd, int a, int b, int c, int d);

void SNDi_SetTrackParam(int player, unsigned int trackMask, int param, int value, int immediate) {
    PushCommand_impl(7, player | (immediate << 24), trackMask, param, value);
}
