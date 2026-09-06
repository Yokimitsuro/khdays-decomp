/* Allocate and populate the five message-record caches used by the main menu. */
typedef unsigned int u32;

typedef struct Ov008Message15Record { char data[0x9c]; } Ov008Message15Record;
typedef struct Ov008Message1BRecord { char data[0x18]; } Ov008Message1BRecord;
typedef struct Ov008Message14Record { char data[0x58]; } Ov008Message14Record;
typedef struct Ov008Message13Record { char data[0x30]; } Ov008Message13Record;
typedef struct Ov008DynamicMessageRecord { char data[0x3e0]; } Ov008DynamicMessageRecord;

typedef struct Ov008MessageCacheContextView {
    char unknown0000[0x207c];
    Ov008Message15Record *pMessage15Records;
    Ov008Message1BRecord *pMessage1BRecords;
    Ov008Message14Record *pMessage14Records;
    Ov008Message13Record *pMessage13Records;
    Ov008DynamicMessageRecord *pDynamicMessageRecords;
    char unknown2090[0x0c];
    int dynamicMessageDbId;
} Ov008MessageCacheContextView;

extern void *NNSi_FndAllocFromDefaultExpHeap(u32 size);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern int func_020342e8(void **record, int dbId, u32 index, int selector);

void func_ov008_0205c780(Ov008MessageCacheContextView *context)
{
    int index15;
    int offset15;
    int byteOffset1b;
    int recordIndex1b;
    int byteOffset14;
    int recordIndex14;
    int byteOffset13;
    int recordIndex13;
    int byteOffsetDynamic;
    int recordIndexDynamic;
    void *record15;
    void *record1b;
    void *record14;
    void *record13;
    void *recordDynamic;

    context->pMessage15Records = NNSi_FndAllocFromDefaultExpHeap(0x18084);
    context->pMessage1BRecords = NNSi_FndAllocFromDefaultExpHeap(0x5e8);
    context->pMessage14Records = NNSi_FndAllocFromDefaultExpHeap(0x840);
    context->pMessage13Records = NNSi_FndAllocFromDefaultExpHeap(0x15c0);
    context->pDynamicMessageRecords = NNSi_FndAllocFromDefaultExpHeap(0xc1c0);
    MI_CpuFill8(context->pMessage15Records, 0, 0x9c);

    index15 = 1;
    offset15 = 0x9c;
    do {
        record15 = (char *)context->pMessage15Records + offset15;
        func_020342e8(&record15, 0x15, index15, -1);
        index15++;
        offset15 += 0x9c;
    } while (index15 < 0x277);

    byteOffset1b = recordIndex1b = 0;
    do {
        record1b = (char *)context->pMessage1BRecords + byteOffset1b;
        func_020342e8(&record1b, 0x1b, recordIndex1b, -1);
        recordIndex1b++;
        byteOffset1b += 0x18;
    } while (recordIndex1b < 0x3f);

    byteOffset14 = recordIndex14 = 0;
    do {
        record14 = (char *)context->pMessage14Records + byteOffset14;
        func_020342e8(&record14, 0x14, recordIndex14, -1);
        recordIndex14++;
        byteOffset14 += 0x58;
    } while (recordIndex14 < 0x18);

    byteOffset13 = recordIndex13 = 0;
    do {
        record13 = (char *)context->pMessage13Records + byteOffset13;
        func_020342e8(&record13, 0x13, recordIndex13, -1);
        recordIndex13++;
        byteOffset13 += 0x30;
    } while (recordIndex13 < 0x74);

    byteOffsetDynamic = recordIndexDynamic = 0;
    do {
        recordDynamic = (char *)context->pDynamicMessageRecords + byteOffsetDynamic;
        func_020342e8(&recordDynamic, context->dynamicMessageDbId, recordIndexDynamic, -1);
        recordIndexDynamic++;
        byteOffsetDynamic += 0x3e0;
    } while (recordIndexDynamic < 0x32);
}
