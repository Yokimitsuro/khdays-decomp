typedef struct Ov005Context {
    char header[0x54];
    char embeddedManager[0x4a80];
    char opaque4ad4[0x13c];
    unsigned char dialogChoice;
} Ov005Context;
extern Ov005Context *data_ov005_0205b80c;
extern int func_ov005_0204e0d0(void *,int);
extern void func_ov005_0204e400(void *,int);
extern void func_ov005_0204e29c(void *,int,int);
static inline void SetVisible(int id,int visible) {
    int entry=func_ov005_0204e0d0(data_ov005_0205b80c->embeddedManager,id);
    func_ov005_0204e29c(data_ov005_0205b80c->embeddedManager,entry,visible);
}
void func_ov005_020544f4(void) {
    Ov005Context *context=data_ov005_0205b80c;
    int entry;
    if(context->dialogChoice) {
        entry=func_ov005_0204e0d0(context->embeddedManager,25);
        func_ov005_0204e400(context->embeddedManager,entry);
        SetVisible(27,1);
        SetVisible(28,0);
    } else {
        entry=func_ov005_0204e0d0(context->embeddedManager,26);
        func_ov005_0204e400(context->embeddedManager,entry);
        SetVisible(27,0);
        SetVisible(28,1);
    }
}
