/* func_ov005_0205873c -- play SFX 0x13 and reset the ov005 blink timer, ov005. */
extern void func_02030d10(int soundId);
extern int data_ov005_0205b8d0;
void func_ov005_0205873c(void) {
    func_02030d10(0x13);
    data_ov005_0205b8d0 = 0;
}
