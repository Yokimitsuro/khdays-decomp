typedef unsigned char u8;
typedef struct Ov005ExitTask { unsigned receivedPlayerMask; int protocolPhase; } Ov005ExitTask;
extern Ov005ExitTask *data_ov005_0205b8d0;
extern const char *data_ov005_0205b79c[3];
extern unsigned func_02030788(void);
extern int func_0201fabc(const char *,const char *);
void func_ov005_0205875c(const u8 *message,int size) {
    Ov005ExitTask *task=data_ov005_0205b8d0;
    if(task==0)return;
    if(func_02030788()==0) {
        if(size!=23)return;
        if(func_0201fabc((const char *)message+1,data_ov005_0205b79c[2])==0)
            task->receivedPlayerMask|=1u<<message[0];
    } else if(task->protocolPhase==0) {
        if(func_0201fabc((const char *)message,data_ov005_0205b79c[1])==0)
            task->receivedPlayerMask|=1;
    } else {
        if(func_0201fabc((const char *)message,data_ov005_0205b79c[0])==0)
            task->protocolPhase=2;
    }
}
