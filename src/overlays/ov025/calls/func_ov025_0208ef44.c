/* Resolve a message-record pointer from ov008 caches or the generic database. */
typedef unsigned int u32;

typedef struct Ov008MessageCacheContextView {
    char unknown0000[0x207c];
    int pMessage15Records;
    int pMessage1BRecords;
    int pMessage14Records;
    int pMessage13Records;
    int pDynamicMessageRecords;
    char unknown2090[0x0c];
    int dynamicMessageDbId;
} Ov008MessageCacheContextView;

extern Ov008MessageCacheContextView *func_ov025_02084afc(void);
extern int func_020342e8(int *record, int dbId, u32 index, int selector);

int func_ov025_0208ef44(int *record, int dbId, u32 index, int selector)
{
    Ov008MessageCacheContextView *context;
    int result;

    context = func_ov025_02084afc();
    result = 1;
    if (dbId == context->dynamicMessageDbId) {
        *record = context->pDynamicMessageRecords + index * 0x3e0;
        return result;
    }
    switch (dbId) {
    case 0x15:
        *record = context->pMessage15Records + index * 0x9c;
        break;
    case 0x1b:
        *record = context->pMessage1BRecords + index * 0x18;
        break;
    case 0x14:
        *record = context->pMessage14Records + index * 0x58;
        break;
    case 0x13:
        *record = context->pMessage13Records + index * 0x30;
        break;
    default:
        result = func_020342e8(record, dbId, index, selector);
        break;
    }
    return result;
}
