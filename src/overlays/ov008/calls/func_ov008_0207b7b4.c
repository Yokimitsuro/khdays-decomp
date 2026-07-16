/* func_ov008_0207b7b4 -- read the confirmed menu selection.
 * While idle (base+0x4e8 == 0) returns the live cursor selection
 * (WM_EndKeySharing_0x020bf240); once locked in it returns -1.
 *
 * PROVENANCE: byte-identical twin of func_ov006_0204fa58, propagated from it. The "Mission Mode"
 * framing in that rep is ov006's own scene identity -- ov008 loads the same UI/mlt/* resources,
 * so it is plausible here, but it has not been verified for THIS function. Not asserted. */
extern int WM_EndKeySharing_0x020bf240(void);
extern int data_ov008_02090f24;

int func_ov008_0207b7b4(void) {
    int sel;
    if (*(int *)(data_ov008_02090f24 + 0x4e8) != 0) {
        sel = -1;
    } else {
        sel = WM_EndKeySharing_0x020bf240();
    }
    return (char)sel;
}
