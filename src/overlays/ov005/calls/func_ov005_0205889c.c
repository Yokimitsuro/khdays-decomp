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
extern const char *data_ov005_0205b79c[3];
extern void func_0201f924(char *,const char *);
extern unsigned func_02031258(int,const void *,unsigned);
extern void *func_ov005_020588f0(void);
ExitTaskState func_ov005_0205889c(void) {
    Ov005ExitTask *task=NNSi_FndGetCurrentRootHeap();
    ExitTaskState nextState=0;
    if(task->receivedPlayerMask!=0) {
        func_0201f924(task->clientMessage.text,data_ov005_0205b79c[2]);
        func_02031258(19,&task->clientMessage,23);
        task->protocolPhase=1;
        nextState=func_ov005_020588f0;
    }
    return nextState;
}
