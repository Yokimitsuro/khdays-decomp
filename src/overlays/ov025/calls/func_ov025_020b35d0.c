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
extern int func_ov025_020b0e3c(void);
extern int func_ov025_020b0e58(int c);
extern int func_ov025_020b1084(int c);
extern int func_ov025_020b12b0(int c);
extern int func_ov025_020b14dc(int c);
extern int func_ov025_020b1708(int c);
extern int func_ov025_020b1934(int c);
extern int func_ov025_020b1b60(int c);
extern int func_ov025_020b1d8c(int c);
extern int func_ov025_020b1fb8(int c);
extern int func_ov025_020b21e4(int c);
extern int func_ov025_020b2410(int c);
extern int func_ov025_020b263c(int c);
extern int func_ov025_020b2868(int c);
extern int func_ov025_020b2a94(int c);
extern int func_ov025_020b2cc0(int c);
extern int func_ov025_020b2eec(int c);
extern int func_ov025_020b3118(int c);
extern int func_ov025_020b3344(int c);

u16 *func_ov025_020b35d0(Ov005DescriptionCache *cache, MsgDbItemRecord *item) {
    int originalRecordId;
    int mappedRecordId;

    if (item == 0) {
        return 0;
    }
    originalRecordId = item->descriptionRecordId;
    if (cache->record != 0) {
        cache->releaseCallback(&cache->record);
    }
    switch (func_ov025_020b0e3c()) {
    case 1:  mappedRecordId = func_ov025_020b0e58(originalRecordId); break;
    case 6:  mappedRecordId = func_ov025_020b1084(originalRecordId); break;
    case 17: mappedRecordId = func_ov025_020b12b0(originalRecordId); break;
    case 18: mappedRecordId = func_ov025_020b14dc(originalRecordId); break;
    case 7:  mappedRecordId = func_ov025_020b1708(originalRecordId); break;
    case 8:  mappedRecordId = func_ov025_020b1934(originalRecordId); break;
    case 9:  mappedRecordId = func_ov025_020b1b60(originalRecordId); break;
    case 10: mappedRecordId = func_ov025_020b1d8c(originalRecordId); break;
    case 16: mappedRecordId = func_ov025_020b1fb8(originalRecordId); break;
    case 11: mappedRecordId = func_ov025_020b21e4(originalRecordId); break;
    case 0:
    case 14:
    case 19: mappedRecordId = func_ov025_020b2410(originalRecordId); break;
    case 3:  mappedRecordId = func_ov025_020b263c(originalRecordId); break;
    case 5:  mappedRecordId = func_ov025_020b2868(originalRecordId); break;
    case 12: mappedRecordId = func_ov025_020b2a94(originalRecordId); break;
    case 4:  mappedRecordId = func_ov025_020b2cc0(originalRecordId); break;
    case 13: mappedRecordId = func_ov025_020b2eec(originalRecordId); break;
    case 2:  mappedRecordId = func_ov025_020b3118(originalRecordId); break;
    case 15: mappedRecordId = func_ov025_020b3344(originalRecordId); break;
    default: mappedRecordId = originalRecordId; break;
    }
    if (mappedRecordId == originalRecordId) {
        return item->description;
    }
    cache->loadCallback(&cache->record, 0x15, mappedRecordId, 0xe);
    return cache->record->description;
}
