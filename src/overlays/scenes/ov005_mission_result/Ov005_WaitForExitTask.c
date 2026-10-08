/* Waits for the exit synchronisation task to finish, then releases it and leaves. */

typedef struct Ov005Context {
    char opaque00[0x4bf0];
    int menuState;
    char opaque4bf4[0x5d5a0];
    void *exitTaskHandle;
} Ov005Context;
extern Ov005Context *data_ov005_0205b80c;
extern void Ov005_UpdateDialogVisibility(void);
extern int Ov005_IsSubContextUsable(void);
extern void VeneerTo_Obj_Destroy(void *);
void Ov005_WaitForExitTask(void) {
    Ov005_UpdateDialogVisibility();
    if(Ov005_IsSubContextUsable()==0)return;
    VeneerTo_Obj_Destroy(data_ov005_0205b80c->exitTaskHandle);
    data_ov005_0205b80c->exitTaskHandle=0;
    data_ov005_0205b80c->menuState=6;
}
