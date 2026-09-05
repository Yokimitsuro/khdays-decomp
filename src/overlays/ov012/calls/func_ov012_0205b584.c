typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ov012OpeningEvent {
    u32 nTriggerThreadDelta;
    u16 uHandlerIndex;
    u8 aPayload[6];
} Ov012OpeningEvent;

typedef int (*Ov012OpeningEventHandler)(void *pContext, u32 nThreadDelta,
                                         Ov012OpeningEvent *pEvent);

extern Ov012OpeningEventHandler data_ov012_0205c2a4[];
extern Ov012OpeningEvent data_ov012_0205c310[];
extern void func_0201e374(int brightness);

void func_ov012_0205b584(void *pContext, u32 nThreadDelta) {
    char *context;
    int *pEventIndex;
    Ov012OpeningEventHandler *pHandlers;
    Ov012OpeningEvent *pEvent;

    context = (char *)pContext;
    pEvent = data_ov012_0205c310 + *(int *)(context + 0x8dec);
    if ((*(u16 *)(context + 2) & 4) != 0) {
        return;
    }

    if (pEvent->nTriggerThreadDelta <= nThreadDelta) {
        pEventIndex = (int *)(context + 0x8dec);
        pHandlers = data_ov012_0205c2a4;
        do {
            if (pHandlers[pEvent->uHandlerIndex](
                    pContext, nThreadDelta, pEvent) == 0) {
                break;
            }
            (*pEventIndex)++;
            pEvent++;
        } while (pEvent->nTriggerThreadDelta <= nThreadDelta);
    }

    func_0201e374(*(int *)(context + 0x8bf4));
}
