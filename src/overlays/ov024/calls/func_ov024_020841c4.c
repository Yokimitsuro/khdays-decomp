/* func_ov024_020841c4 -- MobiClip player: silence and release the video's audio channel.
 * Mutes channel 3, waits for the sound command queue to drain around stopping the timer, then
 * unlocks the channel and waits again. */
extern void SND_SetChannelVolume(int ch, int a, int b);
extern unsigned int func_020089e8(void);
extern void func_020087c0(int a);
extern void SND_WaitForCommandProc(unsigned int tag);
extern void SND_StopTimer(int ch, int a, int b, int c);
extern void SND_UnlockChannel(int ch, int a);

void func_ov024_020841c4(void) {
    unsigned int tag;

    SND_SetChannelVolume(3, 0, 0);
    tag = func_020089e8();
    func_020087c0(1);
    SND_WaitForCommandProc(tag);
    SND_StopTimer(3, 0, 0, 0);
    SND_UnlockChannel(3, 0);
    func_020087c0(1);
}
