extern int GX_DisableBankForSubBGExtPltt();

extern int data_020446f0;

void GXS_BeginLoadBGExtPltt(void) {
    data_020446f0 = GX_DisableBankForSubBGExtPltt();
}
