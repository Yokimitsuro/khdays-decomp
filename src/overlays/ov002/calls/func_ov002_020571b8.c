typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ov002PanelContext {
    unsigned char gap0000[0x18c];
    int nPanelState;
} Ov002PanelContext;

extern Ov002PanelContext *data_ov002_0207f614;

extern void G2x_SetBlendAlpha_(u32 *pRegister, u32 nFirstTarget,
                               u32 nSecondTarget, u32 nEva, u32 nEvb);
extern void G2x_SetBlendBrightness_(u16 *pRegister, u32 nPlaneMask,
                                    int nBrightness);
extern void func_ov002_0205f544(void);
extern int func_ov002_02063888(void);

/* Keep the panel blend registers synchronized with the active request state. */
void func_ov002_020571b8(void)
{
    int nPanelState;

    if (data_ov002_0207f614 == 0) {
        return;
    }
    nPanelState = data_ov002_0207f614->nPanelState;
    if (nPanelState >= 9 && nPanelState <= 11) {
        G2x_SetBlendAlpha_((u32 *)0x04000050, 8, 0x21, 3, 0xd);
        func_ov002_0205f544();
        return;
    }
    if (func_ov002_02063888() != 0) {
        G2x_SetBlendBrightness_((u16 *)0x04001050, 0x2c, -8);
    }
    G2x_SetBlendAlpha_((u32 *)0x04000050, 8, 0x21, 0x10, 0);
}
