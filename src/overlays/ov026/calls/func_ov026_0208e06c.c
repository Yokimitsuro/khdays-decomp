/* func_ov026_0208e06c -- Ov008_FreeParamTable: release the param table.  For
 * each of the five record lists: list 0 (shop items, db 0x15) releases the raw
 * db record held at each entry's +0xc; lists 3 and 4 (rewards) free the text
 * buffer (+0x18) of every entry without an item definition (+0xc == 0); every
 * list's array is then freed and cleared.  Finally the listed-pointer array
 * (+0x38) and the table itself are freed.
 */
typedef unsigned char u8;
typedef unsigned int  u32;

#define LIST_COUNT 5
#define LIST_SHOP  0
#define LIST_REWARD_FIRST 3

typedef struct Ov008ParamRecord {
    u8    pad_00[0xc];
    void *pItemDef;           /* 0x0c: shop: raw db record; reward: item definition or 0 */
    u8    pad_10[8];
    void *pText;              /* 0x18: reward: owned text buffer */
    u8    pad_1c[0x34 - 0x1c];
} Ov008ParamRecord;

typedef struct Ov008ParamTable {
    u32 aCount[LIST_COUNT];               /* 0x00 */
    Ov008ParamRecord *apRecords[LIST_COUNT]; /* 0x14 */
    u8  pad_28[0x38 - 0x28];
    void *apListed;                       /* 0x38 */
} Ov008ParamTable;

extern Ov008ParamTable *data_ov026_0209136c;
extern void func_020343cc(void **ppRaw);                              /* release a raw db record */
extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);

void func_ov026_0208e06c(void)
{
    int nList;
    u32 i;
    Ov008ParamRecord *pRecords;

    for (nList = 0; nList < LIST_COUNT; nList++) {
        pRecords = data_ov026_0209136c->apRecords[nList];
        if (pRecords != 0) {
            if (nList == LIST_SHOP) {
                for (i = 0; i < data_ov026_0209136c->aCount[nList]; i++) {
                    func_020343cc(&pRecords[i].pItemDef);
                }
            } else if (nList >= LIST_REWARD_FIRST) {
                for (i = 0; i < data_ov026_0209136c->aCount[nList]; i++) {
                    if (pRecords[i].pItemDef == 0) {
                        NNSi_FndFreeFromDefaultHeap(pRecords[i].pText);
                    }
                }
            }
            NNSi_FndFreeFromDefaultHeap(pRecords);
            data_ov026_0209136c->apRecords[nList] = 0;
        }
    }
    if (data_ov026_0209136c->apListed != 0) {
        NNSi_FndFreeFromDefaultHeap(data_ov026_0209136c->apListed);
        data_ov026_0209136c->apListed = 0;
    }
    NNSi_FndFreeFromDefaultHeap(data_ov026_0209136c);
}
