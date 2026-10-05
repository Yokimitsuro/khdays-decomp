/* Ov008_DrawListEntryRow -- Ov008_DrawListEntryRow (804 B, 28 relocs).
 * Renders one entry row of the mission/status menu list at grid column `col`. Picks the row's
 * icon by entry kind (node[2], 0..5 via a jump table; some kinds pick a variant tag from node[7])
 * and applies it to the icon layer; if node[6] is set it also lights tag 3. Builds the label text
 * into a local 64-halfword UTF-16 buffer -- copied verbatim from node[5] when node[3] < 0, else
 * mapped through Ov008_VariadicMapForward(0x37, ..., node[5], node[3]) -- and draws it (Text_DrawWithShadow),
 * swapping the palette pointer at self+0x1b0 to the overflow palette when the text overruns 0x4c.
 * When node[4] > 0 it also formats a value string (kind 3 maps via 0x38; kind 5 with id 0x5a uses
 * one format, everything else another) and draws it twice at columns +4/+3 (Text_DrawDirectional_2).
 * Called per visible entry by Ov008_DrawListWindow (Ov008_DrawListWindow). Row cell = col*16.
 * Crack: compute `row = col*16` AFTER the overrun `if` so the MaxOverRun result's register frees
 * for the &buf argument; the switch bodies are laid out in source order 1,5,0,4,3,2. */
extern const char data_ov008_020907e0[];
extern const char data_ov008_020907e8[];

extern int  Ov008_GetCtxBlock954c(void);
extern int  Ov008_GetCtxBlock968c(void);
extern int  Ov008_GetDescriptor3(void);
extern int  Ov008_FindEntryByTag(int list, int tag);
extern void Ov008_ApplyTempFieldsAndRestore(int block, int entry, int a, int b);
extern void *Ov008_VariadicMapForward(void *pMsg, int nKind, void *pOut, int nSize, ...);
extern void StrNCopy16(void *dst, void *src, int n);
extern int  NNSi_G2dFontGetTextWidth(int a, int b, void *buf);
extern void Text_DrawWithShadow(int a, int b, int c, int d, void *e, int f);
extern void Text_FormatUtf16(unsigned short *dst, unsigned int len, const unsigned short *fmt, ...);
extern void Text_DrawDirectional_2(int a, int b, int c, int d, int e, void *buf);

void Ov008_DrawListEntryRow(int self, int col, int *node)
{
    int block1, block2, iVar3, entry, iVar5, row;
    unsigned short uVar4;
    short buf[64];

    block1 = Ov008_GetCtxBlock954c();
    block2 = Ov008_GetCtxBlock968c();
    iVar3 = Ov008_GetDescriptor3();
    switch (node[2]) {
    case 1:
        uVar4 = node[7] != 0 ? 0xb : 5;
        entry = Ov008_FindEntryByTag(block1, uVar4);
        Ov008_ApplyTempFieldsAndRestore(block1, entry, 0, (short)(col << 1));
        break;
    case 5:
        uVar4 = node[7] != 0 ? 0xa : 4;
        entry = Ov008_FindEntryByTag(block1, uVar4);
        Ov008_ApplyTempFieldsAndRestore(block1, entry, 0, (short)(col << 1));
        break;
    case 0:
        uVar4 = node[7] != 0 ? 0xc : 6;
        entry = Ov008_FindEntryByTag(block1, uVar4);
        Ov008_ApplyTempFieldsAndRestore(block1, entry, 0, (short)(col << 1));
        break;
    case 4:
        entry = Ov008_FindEntryByTag(block1, 7);
        Ov008_ApplyTempFieldsAndRestore(block1, entry, 0, (short)(col << 1));
        break;
    case 3:
        uVar4 = node[7] != 0 ? 0xe : 8;
        entry = Ov008_FindEntryByTag(block1, uVar4);
        Ov008_ApplyTempFieldsAndRestore(block1, entry, 0, (short)(col << 1));
        break;
    case 2:
        entry = Ov008_FindEntryByTag(block1, 9);
        Ov008_ApplyTempFieldsAndRestore(block1, entry, 0, (short)(col << 1));
        break;
    }
    if (node[6] != 0) {
        entry = Ov008_FindEntryByTag(block1, 3);
        Ov008_ApplyTempFieldsAndRestore(block1, entry, 0xf, (short)(col << 1));
    }
    if (node[3] >= 0)
        Ov008_VariadicMapForward((void *)(self + 0x58), 0x37, buf, 0x40, node[5], node[3]);
    else
        StrNCopy16(buf, (void *)node[5], 0x40);
    buf[63] = 0;
    iVar5 = NNSi_G2dFontGetTextWidth(*(int *)(self + 0x1b0), *(int *)(self + 0x1b4), buf);
    if (iVar5 >= 0x4d)
        *(int *)(self + 0x1b0) = iVar3;
    row = col << 4;
    Text_DrawWithShadow(self + 0x190, 0x10, row + 3, 0xf2, buf, 1);
    *(int *)(self + 0x1b0) = block2;
    if (node[4] > 0) {
        *(int *)(self + 0x1b0) = iVar3;
        if (node[2] == 3) {
            Ov008_VariadicMapForward((void *)(self + 0x58), 0x38, buf, 0x40, node[4]);
        } else if (node[2] == 5 && node[0] == 0x5a) {
            Text_FormatUtf16(buf, 0x40, (const unsigned short *)data_ov008_020907e0, node[4]);
        } else {
            Text_FormatUtf16(buf, 0x40, (const unsigned short *)data_ov008_020907e8, node[4]);
        }
        buf[63] = 0;
        Text_DrawDirectional_2(self + 0x190, 0x71, row + 4, 0xf1, 0x821, buf);
        Text_DrawDirectional_2(self + 0x190, 0x70, row + 3, 0xf2, 0x821, buf);
        *(int *)(self + 0x1b0) = block2;
    }
}
