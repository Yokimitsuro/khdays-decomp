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
extern int func_ov005_0205896c(void);
extern int func_ov005_02058988(int c);
extern int func_ov005_02058bb4(int c);
extern int func_ov005_02058de0(int c);
extern int func_ov005_0205900c(int c);
extern int func_ov005_02059238(int c);
extern int func_ov005_02059464(int c);
extern int func_ov005_02059690(int c);
extern int func_ov005_020598bc(int c);
extern int func_ov005_02059ae8(int c);
extern int func_ov005_02059d14(int c);
extern int func_ov005_02059f40(int c);
extern int func_ov005_0205a16c(int c);
extern int func_ov005_0205a398(int c);
extern int func_ov005_0205a5c4(int c);
extern int func_ov005_0205a7f0(int c);
extern int func_ov005_0205aa1c(int c);
extern int func_ov005_0205ac48(int c);
extern int func_ov005_0205ae74(int c);

u16 *func_ov005_0205b100(Ov005DescriptionCache *cache, MsgDbItemRecord *item) {
    int originalRecordId;
    int mappedRecordId;

    if (item == 0) {
        return 0;
    }
    originalRecordId = item->descriptionRecordId;
    if (cache->record != 0) {
        cache->releaseCallback(&cache->record);
    }
    switch (func_ov005_0205896c()) {
    case 1:  mappedRecordId = func_ov005_02058988(originalRecordId); break;
    case 6:  mappedRecordId = func_ov005_02058bb4(originalRecordId); break;
    case 17: mappedRecordId = func_ov005_02058de0(originalRecordId); break;
    case 18: mappedRecordId = func_ov005_0205900c(originalRecordId); break;
    case 7:  mappedRecordId = func_ov005_02059238(originalRecordId); break;
    case 8:  mappedRecordId = func_ov005_02059464(originalRecordId); break;
    case 9:  mappedRecordId = func_ov005_02059690(originalRecordId); break;
    case 10: mappedRecordId = func_ov005_020598bc(originalRecordId); break;
    case 16: mappedRecordId = func_ov005_02059ae8(originalRecordId); break;
    case 11: mappedRecordId = func_ov005_02059d14(originalRecordId); break;
    case 0:
    case 14:
    case 19: mappedRecordId = func_ov005_02059f40(originalRecordId); break;
    case 3:  mappedRecordId = func_ov005_0205a16c(originalRecordId); break;
    case 5:  mappedRecordId = func_ov005_0205a398(originalRecordId); break;
    case 12: mappedRecordId = func_ov005_0205a5c4(originalRecordId); break;
    case 4:  mappedRecordId = func_ov005_0205a7f0(originalRecordId); break;
    case 13: mappedRecordId = func_ov005_0205aa1c(originalRecordId); break;
    case 2:  mappedRecordId = func_ov005_0205ac48(originalRecordId); break;
    case 15: mappedRecordId = func_ov005_0205ae74(originalRecordId); break;
    default: mappedRecordId = originalRecordId; break;
    }
    if (mappedRecordId == originalRecordId) {
        return item->description;
    }
    cache->loadCallback(&cache->record, 0x15, mappedRecordId, 0xe);
    return cache->record->description;
}
