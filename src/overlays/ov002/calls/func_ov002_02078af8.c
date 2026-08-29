typedef struct Ov002Stage {
    unsigned char aPad[0x4e];
    unsigned short wPitch;              /* +0x4e */
    unsigned char aPad2[4];
    int nBase;                          /* +0x54 */
} Ov002Stage;

typedef struct Ov002SpotHolder {
    int nHead;                          /* +0x00 */
    Ov002Stage *pStage;                 /* +0x04 */
} Ov002SpotHolder;

/* The six byte session packet this builds on the stack. */
typedef struct Ov002SpotCmd {
    unsigned char bMode;                /* +0x00 */
    unsigned char bKind;                /* +0x01, always 0x1f */
    unsigned short wIndex;              /* +0x02 */
    unsigned char bPacked;              /* +0x04 */
    unsigned char bPad;                 /* +0x05 */
} Ov002SpotCmd;

extern Ov002Stage *data_ov002_0207fa28[];

extern int func_02020400(int nNumerator, int nDenominator);
extern int func_02030694(void);
extern void func_ov002_02077f64(int nId, void *pCmd, int nSize);
extern void func_02031258(int nType, void *pCmd, int nSize);
extern int func_02031384(int nType, void *pCmd, int nSize);

int func_ov002_02078af8(int nPos, int nA, unsigned char bB, int nMode)
{
    Ov002SpotCmd cmd;
    Ov002Stage *pStage;

    pStage = data_ov002_0207fa28[1];
    cmd.bMode = (unsigned char)nMode;
    cmd.bKind = 0x1f;
    cmd.wIndex = (unsigned short)func_02020400(nPos - pStage->nBase,
                                               pStage->wPitch);
    cmd.bPacked = (unsigned char)((bB & 0x1f) | (nA << 5));

    if (nMode == 0) {
        if (func_02030694() != 0) {
            func_ov002_02077f64(cmd.wIndex, &cmd, 6);
        } else {
            func_02031258(5, &cmd, 6);
        }
    } else {
        if (func_02031384(5, &cmd, 6) == 0xffff) {
            return 0;
        }
    }
    return 1;
}
