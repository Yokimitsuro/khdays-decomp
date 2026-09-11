/* NitroSDK SND_FlushCommand: hand the reserved command list to the ARM7 over PXI.
   Algorithm cross-checked against pret/pokediamond's
   arm9/lib/NitroSDK/src/SND_command.c (SND_FlushCommand). */

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
extern SNDCommand *data_0204476c[8];
extern SNDCommand data_02044a20[0x100];

extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern void DC_FlushRange(void *address, unsigned int size);
extern SNDCommand *func_020085f0(int block); /* SND_RecvCommandReply */
extern int func_020093e8(int channel, unsigned int data, int err); /* PXI_SendWordByFifo */
extern void RequestCommandProc(void);

int func_020087c0(unsigned int flags) {
    int state = OS_DisableInterrupts();

    if (data_02044748.reservedHead == 0) {
        OS_RestoreInterrupts(state);
        return 1;
    }

    if (data_02044748.sentBlockCount >= 8) {
        if ((flags & 1) == 0) {
            OS_RestoreInterrupts(state);
            return 0;
        }
        do {
            func_020085f0(1);
        } while (data_02044748.sentBlockCount >= 8);
        if (data_02044748.reservedHead == 0) {
            OS_RestoreInterrupts(state);
            return 1;
        }
    }

    DC_FlushRange(data_02044a20, sizeof(data_02044a20));

    if (func_020093e8(7, (unsigned int)data_02044748.reservedHead, 0) < 0) {
        if ((flags & 1) == 0) {
            OS_RestoreInterrupts(state);
            return 0;
        }
        while (data_02044748.sentBlockCount >= 8 ||
               func_020093e8(7, (unsigned int)data_02044748.reservedHead, 0) < 0) {
            OS_RestoreInterrupts(state);
            func_020085f0(0);
            state = OS_DisableInterrupts();
            DC_FlushRange(data_02044a20, sizeof(data_02044a20));
            if (data_02044748.reservedHead == 0) {
                OS_RestoreInterrupts(state);
                return 1;
            }
        }
    }

    data_0204476c[data_02044748.sentRingIndex] = data_02044748.reservedHead;
    data_02044748.sentRingIndex++;
    if (data_02044748.sentRingIndex > 8) {
        data_02044748.sentRingIndex = 0;
    }
    data_02044748.reservedHead = 0;
    data_02044748.reservedTail = 0;
    data_02044748.sentBlockCount++;
    data_02044748.nextTag++;
    OS_RestoreInterrupts(state);

    if ((flags & 2) != 0) {
        RequestCommandProc();
    }
    return 1;
}
