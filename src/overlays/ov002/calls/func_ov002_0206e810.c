typedef struct {
    short nVersion;                     /* +0x000 */
    short aHandles[4];                  /* +0x002, filled with 0xffff */
    unsigned char nCount;               /* +0x00a */
    signed char nCurrent;               /* +0x00b */
    int aOwner[0x20];                   /* +0x00c */
    int aValue[0x20];                   /* +0x08c */
    unsigned char aKind[0x20];          /* +0x10c */
    int aTimer[0x20];                   /* +0x12c */
    int aParam[0x20];                   /* +0x1ac */
    unsigned char aState[0x20];         /* +0x22c */
} Ov002Registry;                        /* 0x24c */

typedef int (*Ov002RegistryProc)(void);

extern Ov002Registry *data_ov002_0207fa04;

extern Ov002Registry *NNSi_FndGetCurrentRootHeap(void);
extern void MIi_CpuClear16(unsigned short nValue, void *pDest, int nSize);
extern int func_ov002_0206e888(void);

/* Allocate the registry, blank every slot table and hand back the tick
 * routine the caller should install. */
Ov002RegistryProc func_ov002_0206e810(void)
{
    Ov002Registry *pRegistry;
    int i;

    pRegistry = NNSi_FndGetCurrentRootHeap();
    data_ov002_0207fa04 = pRegistry;

    pRegistry->nVersion = 1;
    MIi_CpuClear16(0xffff, pRegistry->aHandles, 8);

    pRegistry->nCount = 0;
    pRegistry->nCurrent = -1;

    for (i = 0; i < 0x20; i++) {
        pRegistry->aOwner[i] = 0;
        pRegistry->aValue[i] = 0;
        pRegistry->aKind[i] = 0;
        pRegistry->aTimer[i] = 0;
        pRegistry->aParam[i] = 0;
        pRegistry->aState[i] = 0;
    }

    return func_ov002_0206e888;
}
