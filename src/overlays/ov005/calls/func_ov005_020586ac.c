typedef unsigned char u8;
typedef void *(*ExitTaskState)(void);
typedef struct Ov005ExitTask {
    unsigned receivedPlayerMask;
    int protocolPhase,completionStatus;
    unsigned short sendResult;
    char hostMessage[22];
    struct { u8 playerIndex; char text[22]; } clientMessage;
    u8 unknown3b;
} Ov005ExitTask;
extern Ov005ExitTask *data_ov005_0205b8d0;
extern Ov005ExitTask *NNSi_FndGetCurrentRootHeap(void);
extern void MI_CpuFill8(void *,int,unsigned);
extern unsigned func_02030788(void);
extern void *func_ov005_0205889c(void),*func_ov005_02058818(void);
extern void func_ov005_0205875c(const void *,int);
extern void func_02030cf8(int,void (*)(const void *,int));
ExitTaskState func_ov005_020586ac(void) {
    Ov005ExitTask *task=NNSi_FndGetCurrentRootHeap();
    ExitTaskState nextState;
    data_ov005_0205b8d0=task;
    task->completionStatus=0;
    MI_CpuFill8(task->hostMessage,0,22);
    MI_CpuFill8(&task->clientMessage,0,23);
    task->clientMessage.playerIndex=func_02030788();
    task->protocolPhase=0;
    if(func_02030788()==0) {
        task->receivedPlayerMask=1;
        nextState=func_ov005_02058818;
    } else {
        task->receivedPlayerMask=0;
        nextState=func_ov005_0205889c;
    }
    func_02030cf8(19,func_ov005_0205875c);
    return nextState;
}
