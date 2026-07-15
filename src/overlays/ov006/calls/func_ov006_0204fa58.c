/* func_ov006_0204fa58 -- read the title's confirmed menu selection, ov006.
 * While the title is idle (base+0x4e8 == 0) returns the live cursor selection
 * (WM_EndKeySharing_0x020bf240); once locked in it returns -1. */
extern int WM_EndKeySharing_0x020bf240(void);
extern int data_ov006_020565e4;

int func_ov006_0204fa58(void) {
    int sel;
    if (*(int *)(data_ov006_020565e4 + 0x4e8) != 0) {
        sel = -1;
    } else {
        sel = WM_EndKeySharing_0x020bf240();
    }
    return (char)sel;
}
