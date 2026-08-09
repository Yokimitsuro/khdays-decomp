/* GX_GetBankForBGExtPltt: returns the VRAM bank bits for BG extended palette (+0xe). */

extern int data_020446d4;

int GX_GetBankForBGExtPltt(void) {
    return *(unsigned short *)((int)&data_020446d4 + 0xe);
}
