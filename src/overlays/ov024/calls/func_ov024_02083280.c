/* func_ov024_02083280 -- play SFX 0x14 and raise the ov024 refresh flag, ov024
 * (*(&data_ov024_02093a20+4) -> u16 = 1). */
extern void func_020336a4(int soundId);
extern int data_ov024_02093a20;
void func_ov024_02083280(void) {
    func_020336a4(0x14);
    *(unsigned short *)(*(char **)((char *)&data_ov024_02093a20 + 4)) = 1;
}
