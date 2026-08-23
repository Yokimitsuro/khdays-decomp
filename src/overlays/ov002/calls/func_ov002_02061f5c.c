/*
 * Ov002_DrawMessageCaption - draw the caption for the current message.
 *
 * The text surface is opened with the style the context carries, the message
 * whose id the language table gives for the current entry is expanded into a
 * 256-byte buffer, the line is drawn, and the surface is closed again.
 *
 * ARM.
 */

typedef unsigned short u16;

typedef struct {
    char pad000[0xfc];
    char textCtx[0x7c];
    int nStyle;
    char pad17c[0x38];
    char msgCtx[0x40];
} Ov002TextScene;

extern int data_ov002_0207f62c;
extern int data_0204c254;
extern const int data_ov002_0207e3a0[];

extern void func_02030094(void *pCtx, int nStyle, int nFlags);
extern void func_02030278(void *pCtx, int a, int b, int c, void *pText, int d);

extern int func_ov002_02052844(void *pMsg, int nId);
extern void func_ov002_0205287c(void *pMsg, int nKind, char *pOut, int nSize,
                                int nEntry);

void func_ov002_02061f5c(void)
{
    int nEntry;
    char aText[0x100];
    Ov002TextScene *s;

    s = *(Ov002TextScene **)((char *)&data_ov002_0207f62c + 4);
    func_02030094(s->textCtx, s->nStyle, 0);

    nEntry = func_ov002_02052844(
        s->msgCtx,
        data_ov002_0207e3a0[*(u16 *)((char *)&data_0204c254 + 0xe)]);
    func_ov002_0205287c(s->msgCtx, 0xe, aText, 0x80, nEntry);

    func_02030278(s->textCtx, 0, 0, 5, aText, 0);
    func_02030094(s->textCtx, 0, 0);
}
