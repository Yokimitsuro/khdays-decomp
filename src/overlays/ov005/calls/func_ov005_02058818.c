typedef void *(*ExitTaskState)(void);
typedef struct Ov005ExitTask {
    unsigned receivedPlayerMask;
    int protocolPhase,completionStatus;
    unsigned short sendResult;
    char hostMessage[22];
} Ov005ExitTask;
extern Ov005ExitTask *NNSi_FndGetCurrentRootHeap(void);
extern unsigned func_0203070c(void);
extern const char *data_ov005_0205b79c[3];
extern void func_0201f924(char *,const char *);
extern unsigned func_02031384(int,const void *,unsigned);
extern unsigned func_02031258(int,const void *,unsigned);
extern void *func_ov005_020588f0(void);
ExitTaskState func_ov005_02058818(void) {
    Ov005ExitTask *task=NNSi_FndGetCurrentRootHeap();
    ExitTaskState nextState=0;
    if(task->receivedPlayerMask==func_0203070c()) {
        func_0201f924(task->hostMessage,data_ov005_0205b79c[0]);
        task->sendResult=func_02031384(19,task->hostMessage,22);
        task->protocolPhase=1;
        nextState=func_ov005_020588f0;
    } else {
        func_0201f924(task->hostMessage,data_ov005_0205b79c[1]);
        func_02031258(19,task->hostMessage,22);
    }
    return nextState;
}
