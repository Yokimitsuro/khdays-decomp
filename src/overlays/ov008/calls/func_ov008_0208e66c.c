/* Resolve an item description for the local session member, releasing prior cached records. */
typedef unsigned short u16;
typedef struct MsgDbItemRecord {
    char header[12];
    u16 *name,*description;
    int descriptionRecordId,category,unknown1c;
    u16 icon;
} MsgDbItemRecord;
typedef struct Ov005DescriptionCache {
    MsgDbItemRecord *record;
    int (*loadCallback)(MsgDbItemRecord **,int,unsigned int,int);
    int (*releaseCallback)(MsgDbItemRecord **);
    void *exitTaskHandle;
} Ov005DescriptionCache;
extern int func_ov008_0208bed8(void);
extern int func_ov008_0208bef4(int c);
extern int func_ov008_0208c120(int c);
extern int func_ov008_0208c34c(int c);
extern int func_ov008_0208c578(int c);
extern int func_ov008_0208c7a4(int c);
extern int func_ov008_0208c9d0(int c);
extern int func_ov008_0208cbfc(int c);
extern int func_ov008_0208ce28(int c);
extern int func_ov008_0208d054(int c);
extern int func_ov008_0208d280(int c);
extern int func_ov008_0208d4ac(int c);
extern int func_ov008_0208d6d8(int c);
extern int func_ov008_0208d904(int c);
extern int func_ov008_0208db30(int c);
extern int func_ov008_0208dd5c(int c);
extern int func_ov008_0208df88(int c);
extern int func_ov008_0208e1b4(int c);
extern int func_ov008_0208e3e0(int c);

u16 *func_ov008_0208e66c(Ov005DescriptionCache *cache, MsgDbItemRecord *item) {
    int originalRecordId;
    int mappedRecordId;

    if (item == 0) {
        return 0;
    }
    originalRecordId = item->descriptionRecordId;
    if (cache->record != 0) {
        cache->releaseCallback(&cache->record);
    }
    switch (func_ov008_0208bed8()) {
    case 1:  mappedRecordId = func_ov008_0208bef4(originalRecordId); break;
    case 6:  mappedRecordId = func_ov008_0208c120(originalRecordId); break;
    case 17: mappedRecordId = func_ov008_0208c34c(originalRecordId); break;
    case 18: mappedRecordId = func_ov008_0208c578(originalRecordId); break;
    case 7:  mappedRecordId = func_ov008_0208c7a4(originalRecordId); break;
    case 8:  mappedRecordId = func_ov008_0208c9d0(originalRecordId); break;
    case 9:  mappedRecordId = func_ov008_0208cbfc(originalRecordId); break;
    case 10: mappedRecordId = func_ov008_0208ce28(originalRecordId); break;
    case 16: mappedRecordId = func_ov008_0208d054(originalRecordId); break;
    case 11: mappedRecordId = func_ov008_0208d280(originalRecordId); break;
    case 0:
    case 14:
    case 19: mappedRecordId = func_ov008_0208d4ac(originalRecordId); break;
    case 3:  mappedRecordId = func_ov008_0208d6d8(originalRecordId); break;
    case 5:  mappedRecordId = func_ov008_0208d904(originalRecordId); break;
    case 12: mappedRecordId = func_ov008_0208db30(originalRecordId); break;
    case 4:  mappedRecordId = func_ov008_0208dd5c(originalRecordId); break;
    case 13: mappedRecordId = func_ov008_0208df88(originalRecordId); break;
    case 2:  mappedRecordId = func_ov008_0208e1b4(originalRecordId); break;
    case 15: mappedRecordId = func_ov008_0208e3e0(originalRecordId); break;
    default: mappedRecordId = originalRecordId; break;
    }
    if (mappedRecordId == originalRecordId) {
        return item->description;
    }
    cache->loadCallback(&cache->record, 0x15, mappedRecordId, 0xe);
    return cache->record->description;
}
