typedef struct Ov005Context {
    char opaque00[0x4bf0];
    int menuState;
    char opaque4bf4[0x5d5a0];
    void *exitTaskHandle;
} Ov005Context;
extern Ov005Context *data_ov005_0205b80c;
extern void func_ov005_02054184(void);
extern int func_ov005_02058678(void);
extern void WM_EndKeySharing_0x02023ad0(void *);
void func_ov005_020549bc(void) {
    func_ov005_02054184();
    if(func_ov005_02058678()==0)return;
    WM_EndKeySharing_0x02023ad0(data_ov005_0205b80c->exitTaskHandle);
    data_ov005_0205b80c->exitTaskHandle=0;
    data_ov005_0205b80c->menuState=6;
}
