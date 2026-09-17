/* func_ov025_0209bfa8 -- Ov008_MenuEntrySubCount: the sub-entry count of menu entry nItem
 * (data_ov025_020b4f64); the menu context getter is called first (its result unused). */
typedef unsigned char u8;
typedef short s16;

typedef struct Ov008MenuSubEntry {
    s16 nId;                  /* 0x00 */
    u8  nText;                /* 0x02 */
    u8  nHelpText;            /* 0x03 */
} Ov008MenuSubEntry;

typedef struct Ov008MenuEntryDef {
    s16 nId;                  /* 0x00 */
    u8  nText;                /* 0x02 */
    u8  nHelpText;            /* 0x03 */
    u8  nAnchor;              /* 0x04 */
    u8  nState;               /* 0x05: lock state */
    u8  bEnabled;             /* 0x06 */
    u8  nSubCount;            /* 0x07 */
    Ov008MenuSubEntry aSub[3]; /* 0x08 */
} Ov008MenuEntryDef;

extern Ov008MenuEntryDef data_ov025_020b4f64[];                    /* the menu entry table */

extern void *func_ov025_02084afc(void);                             /* Ov008_GetMenuContext */

int func_ov025_0209bfa8(int nItem)
{
    func_ov025_02084afc();
    return data_ov025_020b4f64[nItem].nSubCount;
}
