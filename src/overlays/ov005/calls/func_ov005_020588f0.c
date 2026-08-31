typedef void *(*ExitTaskState)(void);
typedef struct Ov005ExitClientMessage { unsigned char playerIndex; char text[22]; } Ov005ExitClientMessage;
typedef struct Ov005ExitTask {
    unsigned receivedPlayerMask;
    int protocolPhase,completionStatus;
    unsigned short sendResult;
    char hostMessage[22];
    Ov005ExitClientMessage clientMessage;
} Ov005ExitTask;
extern Ov005ExitTask *NNSi_FndGetCurrentRootHeap(void);
extern unsigned func_02030788(void);
extern int func_02031440(unsigned);
extern unsigned func_02031258(int,const void *,unsigned);
extern void *func_ov005_02058954(void);
ExitTaskState func_ov005_020588f0(void) {
    Ov005ExitTask *task=NNSi_FndGetCurrentRootHeap();
    int complete=0;
    if(func_02030788()==0) {
        if(func_02031440(task->sendResult)==0)complete=1;
    } else {
        if(task->protocolPhase!=1)complete=1;
        else func_02031258(19,&task->clientMessage,23);
    }
    return complete?func_ov005_02058954:0;
}
