typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef unsigned long long u64;
typedef long long s64;
typedef int BOOL;
typedef int OSIntrMode;
typedef void *OSMessage;
typedef volatile unsigned short vu16;
typedef volatile unsigned int vu32;
typedef volatile unsigned char vu8;

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define HW_MAIN_MEM 0x02000000




typedef struct {
    void * prevObject;
    void * nextObject;
} NNSFndLink;
typedef struct {
    void * headObject;
    void * tailObject;
    u16 numObjects;
    u16 offset;
} NNSFndList;
void * NNS_FndGetNextListObject(NNSFndList * list, void * object);
extern void * NNS_FndGetNextListObject (NNSFndList * list, void * object);

/* func_02010154 -- NitroSystem list.c: NNS_FndGetNthListObject. */
void * func_02010154 (NNSFndList * list, u16 index)
{
    int count = 0;
    NNSFndLink * object = NULL;


    while ((object = NNS_FndGetNextListObject(list, object)) != NULL)
    {
        if (index == count) {
            return object;
        }
        count++;
    }
    return NULL;
}
