/* func_ov016_0207fafc -- play the entry's SFX and yield 8 frames, ov016. Passes the
 * entry's sound id (@+0x14) and volume (@+0x16) to func_020235d0; returns 8. */
extern void func_020235d0(int soundId, int volume);
int func_ov016_0207fafc(char *entry) {
    func_020235d0(*(unsigned short *)(entry + 0x14), *(unsigned char *)(entry + 0x16));
    return 8;
}
