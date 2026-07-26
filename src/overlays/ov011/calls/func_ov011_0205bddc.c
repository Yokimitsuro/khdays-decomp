/* func_ov011_0205bddc -- point the scene at its 0x29-entry table and reset the cursor.
 *
 * Clearing bit 0 of the flag byte at +0x23abd is what tells the rest of the scene the
 * list is no longer scrolled.
 *
 * The two halfwords sit at struct offsets past what a strh immediate can encode, so mwcc
 * pools the full offset and uses a register-offset store, deriving the second field as
 * that offset minus two. That is ordinary field access, not a hand-computed address. */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct Ov011Scene {
    u8  pad_00000[0x23abd];
    u8  bFlags;
    u8  pad_23abe[0x23ac8 - 0x23abe];
    u16 wA;
    u16 wB;
    const void *pTable;
} Ov011Scene;

typedef struct Ov011Globals {
    int         nCursor;
    Ov011Scene *pScene;
} Ov011Globals;

extern Ov011Globals data_ov011_0205e960;
extern const u8 data_ov011_0205dea0[];

void func_ov011_0205bddc(void)
{
    data_ov011_0205e960.pScene->pTable = data_ov011_0205dea0;
    data_ov011_0205e960.pScene->wB = 0x29;
    data_ov011_0205e960.pScene->wA = 0;
    data_ov011_0205e960.nCursor = 0;
    data_ov011_0205e960.pScene->bFlags &= ~1;
}
