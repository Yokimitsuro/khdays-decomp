/* func_ov008_0208a2c0 -- Ov008_LoadParamRecords: load message db nDbId (slot 0xf),
 * allocate one 0x34-byte param record per db entry, and fill each record from
 * its raw db record through pfnFill(pRecord, pRaw, nIndex).  Db 0x15 is
 * 1-based and its raw records are not released after use; every other db is
 * 0-based and each raw record is freed.  Returns the db release result.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define DB_SLOT      0xf
#define DB_ONE_BASED 0x15

typedef struct Ov008ParamRecord {
    u8 pad_00[0x34];
} Ov008ParamRecord;

typedef void (*Ov008FillRecordFn)(Ov008ParamRecord *pRecord, void *pRaw, int nIndex);

extern void func_02034150(int nDbId, int nSlot);                        /* MsgDb_LoadDb */
extern u16 func_020342d4(int nDbId);                                    /* record count */
extern void *NNSi_FndAllocFromDefaultExpHeap(u32 nSize);                /* AllocDefault (func_02023660) */
extern void func_020342e8(void **ppRaw, int nDbId, u32 nIndex, int nSlot); /* MsgDb_FetchRecord */
extern void func_020343cc(void **ppRaw);                                /* release a raw record */
extern int func_02034258(int nDbId);                                    /* ResSlot_Release */

int func_ov008_0208a2c0(u32 *pCount, Ov008ParamRecord **ppRecords, Ov008FillRecordFn pfnFill, int nDbId)
{
    u32 i;
    u32 nCount;
    void *pRaw;

    func_02034150(nDbId, DB_SLOT);
    nCount = func_020342d4(nDbId);
    *pCount = nCount;
    *ppRecords = NNSi_FndAllocFromDefaultExpHeap(nCount * sizeof(Ov008ParamRecord));
    for (i = 0; i < nCount; i++) {
        pRaw = 0;
        func_020342e8(&pRaw, nDbId, i + (nDbId == DB_ONE_BASED ? 1 : 0), DB_SLOT);
        pfnFill(&(*ppRecords)[i], pRaw, i);
        if (nDbId != DB_ONE_BASED) {
            func_020343cc(&pRaw);
        }
    }
    return func_02034258(nDbId);
}
