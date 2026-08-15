/* Create and start the next external object slot, then return its index. */
typedef unsigned char u8;

typedef struct Ov107Object {
    u8 gap0000[0x44];
    void (*pCallback)(void);
} Ov107Object;

typedef struct Ov002ObjectSlot {
    Ov107Object *pObject;
    u8 gap0004[0x13];
    u8 nSourceIndex;
} Ov002ObjectSlot;

typedef struct Ov002ObjectContext {
    u8 gap0000[0x1c];
    void *aSources[10];
    Ov002ObjectSlot *pSlots;
    u8 gap0048;
    u8 nSlotCount;
} Ov002ObjectContext;

extern Ov002ObjectContext *data_ov002_0207fa14;

extern Ov107Object *func_ov107_020c0db4(void);
extern void func_ov107_020c2b20(void *pSource, Ov107Object *pObject);
extern void func_ov107_020c1cd4(Ov107Object *pObject);
extern void func_ov002_02072c00(void);

int func_ov002_02073bdc(int nSourceIndex)
{
    Ov002ObjectContext *pContext = data_ov002_0207fa14;
    u8 nSlot = pContext->nSlotCount;

    pContext->pSlots[nSlot].pObject = func_ov107_020c0db4();
    func_ov107_020c2b20(pContext->aSources[nSourceIndex],
                        pContext->pSlots[nSlot].pObject);
    pContext->pSlots[nSlot].pObject->pCallback = func_ov002_02072c00;
    pContext->pSlots[nSlot].nSourceIndex = (u8)nSourceIndex;
    func_ov107_020c1cd4(pContext->pSlots[nSlot].pObject);
    pContext->nSlotCount++;
    return nSlot;
}
