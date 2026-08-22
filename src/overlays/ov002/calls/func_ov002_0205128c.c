/*
 * Ov002_CreateNamedResourceTask - allocate the overlay's shared task object,
 * seed its fields, build its resource name and hand back the tick callback.
 *
 * Takes the id at the head of the caller's descriptor, allocates from the
 * current root heap into the overlay's global slot, clears the head word,
 * writes the two fixed limits at +0x0c and +0x04 and clears +0x40, then formats
 * the resource name from the id and installs it unless the global at
 * LoadGlobalU16At0 reads 0x2a. Finally it copies a pair of words from the
 * overlay's table into the object at +0x20 and +0x24 and returns the callback.
 *
 * THUMB. The two copied words are read BEFORE the allocation and held on the
 * stack across it, which is why they occupy sp+0 and sp+4 below the name
 * buffer at sp+8.
 */

typedef void (*Ov002TickFn)(void);

/* The tick this factory hands back; its parameters are not established here. */
extern void func_ov002_02051318(void);

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void OS_SPrintf(char *pDst, const char *pFmt, ...);
extern int func_02020a9c(void);
extern int func_ov002_020728e8(int nId);
extern void func_ov002_02050cd4(unsigned short *pDst, const char *pName);

typedef struct { int nFirst; int nSecond; } Ov002Pair;

extern Ov002Pair data_ov002_0207db54;  /* copied into the object */
extern char data_ov002_0207e844[];  /* resource name format */
extern int data_ov002_0207f600;     /* slot holding the task object */

Ov002TickFn func_ov002_0205128c(int *pDesc)
{
    char szName[128];
    Ov002Pair sPair;
    int nId;
    int *pObj;
    int nIndex;

    sPair = data_ov002_0207db54;
    nId = *pDesc;
    pObj = (int *)NNSi_FndGetCurrentRootHeap();
    data_ov002_0207f600 = (int)pObj;
    *pObj = 0;
    *(int *)(data_ov002_0207f600 + 0xc) = 0x1f000;
    *(int *)(data_ov002_0207f600 + 4) = 0x2000;
    *(int *)(data_ov002_0207f600 + 0x40) = 0;

    nIndex = func_ov002_020728e8(nId);
    OS_SPrintf(szName, data_ov002_0207e844, nIndex);
    if (func_02020a9c() != 0x2a) {
        func_ov002_02050cd4((unsigned short *)(data_ov002_0207f600 + 0x10),
                            szName);
    }

    pObj = (int *)data_ov002_0207f600;
    *(Ov002Pair *)((char *)pObj + 0x20) = sPair;
    return func_ov002_02051318;
}
