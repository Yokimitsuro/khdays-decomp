extern void NNSi_G3dFuncSbc_NOP(void);
extern void NNSi_G3dFuncSbc_RET(void);
extern void NNSi_G3dFuncSbc_NODE(void);
extern void NNSi_G3dFuncSbc_MTX(void);
extern void NNSi_G3dFuncSbc_MAT(void);
extern void NNSi_G3dFuncSbc_SHP(void);
extern void NNSi_G3dFuncSbc_NODEDESC(void);
extern void NNSi_G3dFuncSbc_BB(void);
extern void NNSi_G3dFuncSbc_BBY(void);
extern void NNSi_G3dFuncSbc_NODEMIX(void);
extern void NNSi_G3dFuncSbc_CALLDL(void);
extern void NNSi_G3dFuncSbc_POSSCALE(void);
extern void NNSi_G3dFuncSbc_ENVMAP(void);
extern void NNSi_G3dFuncSbc_PRJMAP(void);
extern void func_02016284(unsigned seed);
extern void *NNS_G3dFuncSbcTable[];

/* Fill NitroSystem G3D's SBC command table (NNS_G3dFuncSbcTable, in DTCM) with the 14 handlers
 * in command order, NOP to PRJMAP -- the table NNSi_G3dDrawInternal dispatches each SBC byte
 * through -- then seed the PRNG (func_02016284) with 1. */
void G3d_InitSbcFuncTable(void) {
    NNS_G3dFuncSbcTable[0] = (void *)&NNSi_G3dFuncSbc_NOP;
    NNS_G3dFuncSbcTable[1] = (void *)&NNSi_G3dFuncSbc_RET;
    NNS_G3dFuncSbcTable[2] = (void *)&NNSi_G3dFuncSbc_NODE;
    NNS_G3dFuncSbcTable[3] = (void *)&NNSi_G3dFuncSbc_MTX;
    NNS_G3dFuncSbcTable[4] = (void *)&NNSi_G3dFuncSbc_MAT;
    NNS_G3dFuncSbcTable[5] = (void *)&NNSi_G3dFuncSbc_SHP;
    NNS_G3dFuncSbcTable[6] = (void *)&NNSi_G3dFuncSbc_NODEDESC;
    NNS_G3dFuncSbcTable[7] = (void *)&NNSi_G3dFuncSbc_BB;
    NNS_G3dFuncSbcTable[8] = (void *)&NNSi_G3dFuncSbc_BBY;
    NNS_G3dFuncSbcTable[9] = (void *)&NNSi_G3dFuncSbc_NODEMIX;
    NNS_G3dFuncSbcTable[10] = (void *)&NNSi_G3dFuncSbc_CALLDL;
    NNS_G3dFuncSbcTable[11] = (void *)&NNSi_G3dFuncSbc_POSSCALE;
    NNS_G3dFuncSbcTable[12] = (void *)&NNSi_G3dFuncSbc_ENVMAP;
    NNS_G3dFuncSbcTable[13] = (void *)&NNSi_G3dFuncSbc_PRJMAP;
    func_02016284(1);
}
