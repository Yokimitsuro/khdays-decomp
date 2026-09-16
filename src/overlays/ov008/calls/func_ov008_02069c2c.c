extern void func_ov008_02050cd4(void);
extern void func_ov008_02050c54(void);
extern void func_ov008_02069bec(int arg0, int arg1);
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

extern Ov008MenuEntryDef data_ov008_02090598[];

void func_ov008_02069c2c(int arg0, int index, int column)
{
    func_ov008_02050cd4();
    func_ov008_02050c54();
    func_ov008_02069bec(arg0, data_ov008_02090598[(short)index].aSub[column].nId);
}
