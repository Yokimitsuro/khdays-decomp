/* func_ov005_02051408 -- ov005 VRAM bank plan: TEX to bank 2, OBJ ext-palette to 0x60, main BG to
 * 1, main OBJ to 0x10, sub BG to 4, sub OBJ to 8. */
extern void GX_SetBankForTex(int bank);
extern void GX_BeginLoadOBJExtPltt(int bank);
extern void GX_SetBankForBG(int bank);
extern void GX_SetBankForOBJ(int bank);
extern void GX_SetBankForSubBG(int bank);
extern void GX_SetBankForSubOBJ(int bank);

void func_ov005_02051408(void) {
    GX_SetBankForTex(2);
    GX_BeginLoadOBJExtPltt(0x60);
    GX_SetBankForBG(1);
    GX_SetBankForOBJ(0x10);
    GX_SetBankForSubBG(4);
    GX_SetBankForSubOBJ(8);
}
