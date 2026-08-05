/* NitroSDK SND_PushCommand: append an already filled command slot to the sound
   driver's reserved list, under an interrupt lock so the ARM7 flush path cannot
   observe a half-linked list. func_020087c0 later hands reservedHead to the ARM7
   over PXI and clears both list pointers. Ghidra carries the semantic name;
   the build symbol stays func_02008788. */

extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);

typedef struct SNDCommand {
    struct SNDCommand *next;
    unsigned int id;
    unsigned int arg[4];
} SNDCommand;

typedef struct SNDCommandMgr {
    SNDCommand *freeHead;
    unsigned int processedTag;
    SNDCommand *reservedHead;
    SNDCommand *reservedTail;
    SNDCommand *freeTail;
    unsigned int unk14;
    int sentRingIndex;
    int sentBlockCount;
    unsigned int nextTag;
} SNDCommandMgr;

extern SNDCommandMgr data_02044748;

void func_02008788(SNDCommand *command) {
    SNDCommand *tail;
    int state;

    state = OS_DisableInterrupts();
    tail = data_02044748.reservedTail;
    /* The tail store is written into both arms on purpose: hoisting it below the
       if/else creates a merge point at which mwcc rematerialises the work-area
       address, costing one extra ldr. Duplicated, it emits the ROM's predicated
       streq/strne pair with the base kept live in r1. */
    if (tail == 0) {
        data_02044748.reservedHead = command;
        data_02044748.reservedTail = command;
    } else {
        tail->next = command;
        data_02044748.reservedTail = command;
    }
    command->next = 0;
    OS_RestoreInterrupts(state);
}
