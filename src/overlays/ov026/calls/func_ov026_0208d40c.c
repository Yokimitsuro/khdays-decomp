/* func_ov026_0208d40c -- Ov008_GetItemParamWord: the parameter word of the shared
 * table that belongs to one of four special ids; any other id yields 1.  A switch
 * (cases in the ROM's block order 0x1c8, 0x1c9, 0x1a0, 0xe8) gives mwcc's binary compare
 * tree with the four returns out of line; an if-chain never does.
 */
typedef unsigned char u8;

typedef struct Ov008ParamTable {
    u8  pad_000[0x148];
    int nParam1c9;   /* 0x148 */
    int nParam1c8;   /* 0x14c */
    int nParam1a0;   /* 0x150 */
    int nParam0e8;   /* 0x154 */
} Ov008ParamTable;

extern Ov008ParamTable *data_ov026_0209136c;

int func_ov026_0208d40c(int nId)
{
    switch (nId) {
    case 0x1c8:
        return data_ov026_0209136c->nParam1c8;
    case 0x1c9:
        return data_ov026_0209136c->nParam1c9;
    case 0x1a0:
        return data_ov026_0209136c->nParam1a0;
    case 0xe8:
        return data_ov026_0209136c->nParam0e8;
    default:
        return 1;
    }
}
