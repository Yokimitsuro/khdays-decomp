/* Records which banks had to be released for the sub BG extended palette upload. */
extern int GX_DisableBankForSubBGExtPltt(void);
extern int data_020446f0[];

void GXS_BeginLoadBGExtPltt(void) {
    data_020446f0[0] = GX_DisableBankForSubBGExtPltt();
}
