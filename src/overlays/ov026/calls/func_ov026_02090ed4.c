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
extern int func_ov026_0208e740(void);
extern int func_ov026_0208e75c(int c);
extern int func_ov026_0208e988(int c);
extern int func_ov026_0208ebb4(int c);
extern int func_ov026_0208ede0(int c);
extern int func_ov026_0208f00c(int c);
extern int func_ov026_0208f238(int c);
extern int func_ov026_0208f464(int c);
extern int func_ov026_0208f690(int c);
extern int func_ov026_0208f8bc(int c);
extern int func_ov026_0208fae8(int c);
extern int func_ov026_0208fd14(int c);
extern int func_ov026_0208ff40(int c);
extern int func_ov026_0209016c(int c);
extern int func_ov026_02090398(int c);
extern int func_ov026_020905c4(int c);
extern int func_ov026_020907f0(int c);
extern int func_ov026_02090a1c(int c);
extern int func_ov026_02090c48(int c);

u16 *func_ov026_02090ed4(Ov005DescriptionCache *cache, MsgDbItemRecord *item) {
    int originalRecordId;
    int mappedRecordId;

    if (item == 0) {
        return 0;
    }
    originalRecordId = item->descriptionRecordId;
    if (cache->record != 0) {
        cache->releaseCallback(&cache->record);
    }
    switch (func_ov026_0208e740()) {
    case 1:  mappedRecordId = func_ov026_0208e75c(originalRecordId); break;
    case 6:  mappedRecordId = func_ov026_0208e988(originalRecordId); break;
    case 17: mappedRecordId = func_ov026_0208ebb4(originalRecordId); break;
    case 18: mappedRecordId = func_ov026_0208ede0(originalRecordId); break;
    case 7:  mappedRecordId = func_ov026_0208f00c(originalRecordId); break;
    case 8:  mappedRecordId = func_ov026_0208f238(originalRecordId); break;
    case 9:  mappedRecordId = func_ov026_0208f464(originalRecordId); break;
    case 10: mappedRecordId = func_ov026_0208f690(originalRecordId); break;
    case 16: mappedRecordId = func_ov026_0208f8bc(originalRecordId); break;
    case 11: mappedRecordId = func_ov026_0208fae8(originalRecordId); break;
    case 0:
    case 14:
    case 19: mappedRecordId = func_ov026_0208fd14(originalRecordId); break;
    case 3:  mappedRecordId = func_ov026_0208ff40(originalRecordId); break;
    case 5:  mappedRecordId = func_ov026_0209016c(originalRecordId); break;
    case 12: mappedRecordId = func_ov026_02090398(originalRecordId); break;
    case 4:  mappedRecordId = func_ov026_020905c4(originalRecordId); break;
    case 13: mappedRecordId = func_ov026_020907f0(originalRecordId); break;
    case 2:  mappedRecordId = func_ov026_02090a1c(originalRecordId); break;
    case 15: mappedRecordId = func_ov026_02090c48(originalRecordId); break;
    default: mappedRecordId = originalRecordId; break;
    }
    if (mappedRecordId == originalRecordId) {
        return item->description;
    }
    cache->loadCallback(&cache->record, 0x15, mappedRecordId, 0xe);
    return cache->record->description;
}
