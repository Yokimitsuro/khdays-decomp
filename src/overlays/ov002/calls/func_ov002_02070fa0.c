typedef void (*Ov002SlotHookFn)(void);

/* An event slot with a string glued on behind it: the builder hands its result
 * straight to the event-slot registrar, and the registrar links slots through
 * the pointer at +0x18. */
typedef struct Ov002TextItem {
    Ov002SlotHookFn pfnRun;         /* 0x00 */
    Ov002SlotHookFn pfnFree;        /* 0x04 */
    Ov002SlotHookFn pfnRefresh;     /* 0x08 */
    char pad000c[0xc];              /* the slot's own bytes; the registrar
                                       stamps the option index and value here */
    struct Ov002TextItem *pNext;    /* 0x18 */
    char *pText;                    /* 0x1c */
} Ov002TextItem;

extern void *NNSi_FndAllocFromDefaultExpHeap(int nSize);
extern int strlen(const char *pStr);
extern char *strncpy(char *pDst, const char *pSrc, int nLen);

extern void func_ov002_02070f20(void);
extern void func_ov002_02070f3c(void);
extern void func_ov002_02070f4c(void);
extern void func_ov002_02070f08(void);

/* Builds a text item: a slot out of the default expanded heap carrying its own
 * copy of the string, and the three hooks that work on it.
 *
 * The copy is allocated to exactly the string's length plus its terminator, and
 * filled with strncpy of just the length -- so the terminator is written by
 * hand afterwards rather than by the copy.
 *
 * The run hook is the only one that varies: one entry streams the string with
 * no tag, the other behind a fixed two-letter tag.  The other two are the same
 * either way; they free the string and recompute the slot's value.
 *
 * Each hook is only stored when it is not -1, which is what the assignment
 * macro expands to.  All four are ordinary functions so the compares never
 * fire, but the ROM emits them.
 */
Ov002TextItem *func_ov002_02070fa0(int bAlternate, const char *pText)
{
    Ov002TextItem *pItem;
    int nLen;

    pItem = (Ov002TextItem *)NNSi_FndAllocFromDefaultExpHeap(0x20);
    pItem->pNext = 0;
    nLen = strlen(pText);
    pItem->pText = (char *)NNSi_FndAllocFromDefaultExpHeap(nLen + 1);
    strncpy(pItem->pText, pText, nLen);
    pItem->pText[nLen] = 0;

    if (bAlternate != 0) {
        if (func_ov002_02070f20 != (Ov002SlotHookFn)-1) {
            pItem->pfnRun = func_ov002_02070f20;
        }
        if (func_ov002_02070f3c != (Ov002SlotHookFn)-1) {
            pItem->pfnFree = func_ov002_02070f3c;
        }
        if (func_ov002_02070f4c != (Ov002SlotHookFn)-1) {
            pItem->pfnRefresh = func_ov002_02070f4c;
        }
    } else {
        if (func_ov002_02070f08 != (Ov002SlotHookFn)-1) {
            pItem->pfnRun = func_ov002_02070f08;
        }
        if (func_ov002_02070f3c != (Ov002SlotHookFn)-1) {
            pItem->pfnFree = func_ov002_02070f3c;
        }
        if (func_ov002_02070f4c != (Ov002SlotHookFn)-1) {
            pItem->pfnRefresh = func_ov002_02070f4c;
        }
    }
    return pItem;
}
