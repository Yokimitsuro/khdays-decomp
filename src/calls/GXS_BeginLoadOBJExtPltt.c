extern int GX_DisableBankForSubOBJExtPltt();

extern char data_020446f0[];

void GXS_BeginLoadOBJExtPltt(void) {
    *(int *)(data_020446f0 + 0x18) = GX_DisableBankForSubOBJExtPltt();
}
