typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* Software mirror of the VRAM bank state, fields beyond field0/fieldA are
   unknown (see GX_BeginLoadOBJExtPltt.c, GX_SetBankForLCDC.c,
   GX_GetBankForBGExtPltt.c for the parts of this struct that are used
   elsewhere). This function only needs to know it is 13 halfwords wide. */
typedef struct {
    u16 field0;
    u16 field2;
    u16 field4;
    u16 field6;
    u16 field8;
    u16 fieldA;
    u16 fieldC;
    u16 fieldE;
    u16 field10;
    u16 field12;
    u16 field14;
    u16 field16;
    u16 field18;
} VRAMState;

extern VRAMState data_020446d4;

void GX_InitGXState(void) {
    VRAMState *state = &data_020446d4;
    state->field0 = 0;
    state->field2 = 0;
    state->field4 = 0;
    state->field6 = 0;
    state->field8 = 0;
    state->fieldA = 0;
    state->fieldC = 0;
    state->fieldE = 0;
    state->field10 = 0;
    state->field12 = 0;
    state->field14 = 0;
    state->field16 = 0;
    state->field18 = 0;

    /* VRAMCNT_A..D */
    *(volatile u32 *)0x04000240 = 0;
    /* VRAMCNT_E */
    *(volatile u8 *)0x04000244 = 0;
    /* VRAMCNT_F */
    *(volatile u8 *)0x04000245 = 0;
    /* VRAMCNT_G */
    *(volatile u8 *)0x04000246 = 0;
    /* VRAMCNT_H, VRAMCNT_I (WRAMCNT at 0x04000247 left untouched) */
    *(volatile u16 *)0x04000248 = 0;
}
