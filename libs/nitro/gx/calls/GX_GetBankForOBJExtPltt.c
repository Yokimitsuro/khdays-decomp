/* GX_GetBankForOBJExtPltt: returns the VRAM bank bits for OBJ extended palette (+0x10). */

extern int data_02046390;

int GX_GetBankForOBJExtPltt(void) {
    return *(unsigned short *)((int)&data_02046390 + 0x10);
}
