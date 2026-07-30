/* func_ov008_0206c36c -- Ov008_DrawListEntryRow (804 B, 28 relocs).
 * Renders one entry row of the mission/status menu list at grid column `col`. Picks the row's
 * icon by entry kind (node[2], 0..5 via a jump table; some kinds pick a variant tag from node[7])
 * and applies it to the icon layer; if node[6] is set it also lights tag 3. Builds the label text
 * into a local 64-halfword UTF-16 buffer -- copied verbatim from node[5] when node[3] < 0, else
 * mapped through func_ov008_02055cbc(0x37, ..., node[5], node[3]) -- and draws it (func_02030278),
 * swapping the palette pointer at self+0x1b0 to the overflow palette when the text overruns 0x4c.
 * When node[4] > 0 it also formats a value string (kind 3 maps via 0x38; kind 5 with id 0x5a uses
 * one format, everything else another) and draws it twice at columns +4/+3 (func_020301c8).
 * Called per visible entry by func_ov008_0206c690 (Ov008_DrawListWindow). Row cell = col*16.
 * Crack: compute `row = col*16` AFTER the overrun `if` so the MaxOverRun result's register frees
 * for the &buf argument; the switch bodies are laid out in source order 1,5,0,4,3,2. */
extern const char data_ov008_020907e0[];
extern const char data_ov008_020907e8[];

extern int  func_ov008_02050c3c(void);
extern int  func_ov008_02050e74(void);
extern int  func_ov008_02050ea4(void);
extern int  func_ov008_02055808(int list, int tag);
extern void func_ov008_020558b8(int block, int entry, int a, int b);
extern int  func_ov008_02055cbc(int a, int b, void *work, int n, ...);
extern void func_02020104(void *dst, void *src, int n);
extern int  func_02013814(int a, int b, void *buf);
extern void func_02030278(int a, int b, int c, int d, void *e, int f);
extern void func_020262a0(void *buf, int cap, const char *fmt, ...);
extern void func_020301c8(int a, int b, int c, int d, int e, void *buf);

void func_ov008_0206c36c(int self, int col, int *node)
{
    int block1, block2, iVar3, entry, iVar5, row;
    unsigned short uVar4;
    short buf[64];

    block1 = func_ov008_02050c3c();
    block2 = func_ov008_02050e74();
    iVar3 = func_ov008_02050ea4();
    switch (node[2]) {
    case 1:
        uVar4 = node[7] != 0 ? 0xb : 5;
        entry = func_ov008_02055808(block1, uVar4);
        func_ov008_020558b8(block1, entry, 0, (short)(col << 1));
        break;
    case 5:
        uVar4 = node[7] != 0 ? 0xa : 4;
        entry = func_ov008_02055808(block1, uVar4);
        func_ov008_020558b8(block1, entry, 0, (short)(col << 1));
        break;
    case 0:
        uVar4 = node[7] != 0 ? 0xc : 6;
        entry = func_ov008_02055808(block1, uVar4);
        func_ov008_020558b8(block1, entry, 0, (short)(col << 1));
        break;
    case 4:
        entry = func_ov008_02055808(block1, 7);
        func_ov008_020558b8(block1, entry, 0, (short)(col << 1));
        break;
    case 3:
        uVar4 = node[7] != 0 ? 0xe : 8;
        entry = func_ov008_02055808(block1, uVar4);
        func_ov008_020558b8(block1, entry, 0, (short)(col << 1));
        break;
    case 2:
        entry = func_ov008_02055808(block1, 9);
        func_ov008_020558b8(block1, entry, 0, (short)(col << 1));
        break;
    }
    if (node[6] != 0) {
        entry = func_ov008_02055808(block1, 3);
        func_ov008_020558b8(block1, entry, 0xf, (short)(col << 1));
    }
    if (node[3] >= 0)
        func_ov008_02055cbc(self + 0x58, 0x37, buf, 0x40, node[5], node[3]);
    else
        func_02020104(buf, (void *)node[5], 0x40);
    buf[63] = 0;
    iVar5 = func_02013814(*(int *)(self + 0x1b0), *(int *)(self + 0x1b4), buf);
    if (iVar5 >= 0x4d)
        *(int *)(self + 0x1b0) = iVar3;
    row = col << 4;
    func_02030278(self + 0x190, 0x10, row + 3, 0xf2, buf, 1);
    *(int *)(self + 0x1b0) = block2;
    if (node[4] > 0) {
        *(int *)(self + 0x1b0) = iVar3;
        if (node[2] == 3) {
            func_ov008_02055cbc(self + 0x58, 0x38, buf, 0x40, node[4]);
        } else if (node[2] == 5 && node[0] == 0x5a) {
            func_020262a0(buf, 0x40, data_ov008_020907e0, node[4]);
        } else {
            func_020262a0(buf, 0x40, data_ov008_020907e8, node[4]);
        }
        buf[63] = 0;
        func_020301c8(self + 0x190, 0x71, row + 4, 0xf1, 0x821, buf);
        func_020301c8(self + 0x190, 0x70, row + 3, 0xf2, 0x821, buf);
        *(int *)(self + 0x1b0) = block2;
    }
}
