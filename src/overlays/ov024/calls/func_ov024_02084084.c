/* func_ov024_02084084 -- mute channel 3 and stop its stream, ov024. */
extern void SND_SetChannelVolume(int ch, int vol, int flags);
extern void func_020087c0(int);
void func_ov024_02084084(void) {
    SND_SetChannelVolume(3, 0x7f, 0);
    func_020087c0(1);
}
