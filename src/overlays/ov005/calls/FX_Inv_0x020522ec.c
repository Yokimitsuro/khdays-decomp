/* Historical SDK misidentification: this is ov005's texture-refresh/draw wrapper,
 * not FX_Inv. The linkage symbol is retained; ownership follows the actual calls. */
extern int func_ov005_02052048();
extern int func_ov005_02052118();

void FX_Inv_0x020522ec(void) {
    func_ov005_02052048();
    func_ov005_02052118();
}
