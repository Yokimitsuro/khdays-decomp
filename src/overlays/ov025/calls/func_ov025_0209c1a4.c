/* func_ov025_0209c1a4 -- Ov025_Config_SaveValues: write the config page's option values (+0x4e)
 * back to the game-state fields 0x37c4, 0x37bf, 0x37c0 (2 bits), 0x37c3, 0x37c2, 0x37c5, 0x37c6,
 * 0x37c7 and 0x35bf (2 bits), masked to their width; value 7 is not saved.  Twin of ov008
 * 02069eec's first half.  Codegen: the value parameter is declared s16 so the field load is
 * evaluated before the id / width constants (mwcc argument order). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef short          s16;

typedef struct Ov025ConfigPage {
    u8   pad_00[0x4e];
    s16  aValue[10];          /* 0x4e: the option values (7 unused) */
} Ov025ConfigPage;

typedef struct GameState {
    u8   pad_0000[0x810];
    u8   aItemCount[0x8d0];   /* 0x810 */
} GameState;

extern Ov025ConfigPage *func_ov025_02084afc(void);                  /* Ov008_GetPageA */
extern GameState *data_0204be18;
extern void  func_020235e8(int nField, int nBits, s16 nValue);      /* GameState_SetField */
extern u32   func_020235d0(int nField, int nBits);                  /* GameState_GetField */

void func_ov025_0209c1a4(void)
{
    Ov025ConfigPage *pPage;

    pPage = func_ov025_02084afc();
    func_020235e8(0x37c4, 1, pPage->aValue[0] & 1);
    func_020235e8(0x37bf, 1, pPage->aValue[1] & 1);
    func_020235e8(0x37c0, 2, pPage->aValue[2] & 3);
    func_020235e8(0x37c3, 1, pPage->aValue[3] & 1);
    func_020235e8(0x37c2, 1, pPage->aValue[4] & 1);
    func_020235e8(0x37c5, 1, pPage->aValue[5] & 1);
    func_020235e8(0x37c6, 1, pPage->aValue[6] & 1);
    func_020235e8(0x37c7, 2, pPage->aValue[8] & 3);
    func_020235e8(0x35bf, 2, pPage->aValue[9] & 3);
}
