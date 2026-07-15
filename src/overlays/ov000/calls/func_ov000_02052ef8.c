/* func_ov000_02052ef8 -- poll the logo intro sequence, ov000. While the intro step
 * counter (scene block @+0x4b08) is below 3, advances func_ov000_0204f6e0; on its
 * result 3 it sets the "done" flag (@+0x6a48). Otherwise (or on completion) it stamps
 * the current tick (@+0x4ae4) and moves to phase 8 (@+0x4ad0). */
extern char *data_ov000_0205ac24;
extern int  func_ov000_0204f6e0(void);
extern unsigned long long func_020031d4(void);
void func_ov000_02052ef8(void) {
    if (*(int *)(data_ov000_0205ac24 + 0x4b08) < 3) {
        int r = func_ov000_0204f6e0();
        if (r < 0) {
            return;
        }
        if (r == 3) {
            *(int *)(data_ov000_0205ac24 + 0x6a48) =
                (*(int *)(data_ov000_0205ac24 + 0x6a48) & -0x10000) | 1;
            return;
        }
    }
    *(unsigned long long *)(data_ov000_0205ac24 + 0x4ae4) = func_020031d4();
    *(int *)(data_ov000_0205ac24 + 0x4ad0) = 8;
}
