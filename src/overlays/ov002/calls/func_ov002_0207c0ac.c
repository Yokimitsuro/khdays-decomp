typedef unsigned short u16;
typedef unsigned char u8;

extern void *func_ov002_0207687c(char *pElement);
extern int func_ov002_0207c700(char *pElement, char *pAnim, void *pCtx,
                               int nMode, int nRange, void *pOut);
extern void func_ov002_020767ec(void *pElement);
extern void func_ov002_0207be34(char *pElement, short *pAnim, int nTrack,
                                int nParamA, int nParamB, int bEffect);
extern int func_02030788(void);
extern int func_ov002_020766e0(void *pElement, void *pMsg, int nKind);
extern unsigned int func_020235d0(u16 nField, u8 nWidth);
extern void func_020235e8(u16 nField, u8 nWidth, u16 nValue);
extern void func_ov002_02076bd8(char *pElement, int nMode);
extern void func_0202bc30(char *pObj);
extern void func_0202aa9c(u16 *pAnim);

/* Run one step of a line element's second model.
 *
 * Step 0 just keeps the model advancing. Step 2 starts the model's own track,
 * taking the speed from the owner and running the special case the owner names,
 * then moves to step 3. Step 3 advances the model, reports the hit once the
 * owner's distance is reached, and when both the advance and the report are
 * done either turns the model round for its return or, for a short owner,
 * releases the element. Whatever happened, an active model is stepped at the
 * end.
 */
int func_ov002_0207c0ac(char *pElement)
{
    char *pOwner;
    void *pCtx;
    int bDone;
    unsigned int nState;
    u8 aMsg[4];

    pOwner = *(char **)(pElement + 8);
    pCtx = func_ov002_0207687c(pElement);

    switch (*(u8 *)(pElement + 0x2c1)) {
    case 0:
        func_ov002_0207c700(pElement, pElement + 0x1b0, pCtx, 1,
                            *(int *)(pElement + 0x2bc), pElement + 0x2b8);
        break;

    case 2:
        if (*(short *)(pOwner + 0x74) == 0x35) {
            func_ov002_020767ec(pElement);
        }

        *(u8 *)(pElement + 0x2c0) = 1;
        *(int *)(pElement + 0x2bc) = *(short *)(pOwner + 0x7a) << 12;

        func_ov002_0207be34(pElement, (short *)(pElement + 0x1b0),
                            *(u8 *)(pElement + 0x2c0),
                            *(int *)(pElement + 0x2bc), 0, 1);

        *(u16 *)(pElement + 0x12) &= ~8;
        *(u8 *)(pElement + 0x2c1) = 3;
        break;

    case 3:
        bDone = func_ov002_0207c700(pElement, pElement + 0x1b0, pCtx, 0,
                                    *(int *)(pElement + 0x2bc),
                                    pElement + 0x2b8) == 0;

        if ((*(u8 *)(pElement + 0x2c3) & 1) == 0
            && (*(int *)(pElement + 0x2b8) >> 12) >= *(short *)(pOwner + 0x7c)
            && func_02030788() == 0) {
            aMsg[0] = 2;
            if (func_ov002_020766e0(pElement, aMsg, 4) != 0) {
                *(u8 *)(pElement + 0x2c3) |= 1;
            }
        }

        if (bDone && (*(u8 *)(pElement + 0x2c3) & 1) != 0) {
            *(u8 *)(pElement + 0x2c1) = 4;

            if (*(signed char *)(pOwner + 0x78) > 2) {
                *(u8 *)(pElement + 0x2c0) = 2;
                *(int *)(pElement + 0x2bc) = 0;

                nState = func_020235d0(*(u16 *)(pElement + 0x14),
                                       *(u8 *)(pElement + 0x16));
                func_020235e8(*(u16 *)(pElement + 0x14),
                              *(u8 *)(pElement + 0x16),
                              (u16)((nState & ~0xfffe) | 2));

                func_ov002_0207be34(pElement, (short *)(pElement + 0x1b0),
                                    *(u8 *)(pElement + 0x2c0),
                                    *(int *)(pElement + 0x2bc), 0, 0);
            } else if (*(signed char *)(pOwner + 0x7e) != 0) {
                func_ov002_02076bd8(pElement, 0);

                if ((*(u16 *)(pElement + 0x12) & 2) != 0) {
                    func_0202bc30(pElement + 0x2c);
                    *(u16 *)(pElement + 0x12) &= ~2;
                }
            }
        }
        break;
    }

    if ((*(u16 *)(pElement + 0x12) & 4) != 0) {
        func_0202aa9c((u16 *)(pElement + 0x1b0));
    }

    return 0;
}
