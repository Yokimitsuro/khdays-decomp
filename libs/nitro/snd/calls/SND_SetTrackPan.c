/* Track parameter 9 = pan. */
extern void SNDi_SetTrackParam(int player, unsigned int trackMask, int param, int value, int immediate);

void SND_SetTrackPan(int player, unsigned int trackMask, int pan) {
    SNDi_SetTrackParam(player, trackMask, 9, pan, 1);
}
