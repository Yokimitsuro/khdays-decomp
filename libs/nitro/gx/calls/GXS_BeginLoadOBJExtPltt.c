/* Records which banks had to be released for the sub OBJ extended palette upload. */
extern int GX_DisableBankForSubOBJExtPltt(void);
extern int data_020446f0[];

void GXS_BeginLoadOBJExtPltt(void) {
    data_020446f0[6] = GX_DisableBankForSubOBJExtPltt();
}
