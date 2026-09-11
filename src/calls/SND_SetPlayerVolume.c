extern void SNDi_SetPlayerParam(int a, int b, int c, int d);

void SND_SetPlayerVolume(int playerNo, int volume) {
    SNDi_SetPlayerParam(playerNo, 6, volume, 2);
}
