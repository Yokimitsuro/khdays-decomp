typedef struct Ov005Context {
    char header[0x54];
    char embeddedManager[0x4a80];
    char opaque4ad4[0x15c];
    int interactiveEntriesInitialized;
} Ov005Context;
extern Ov005Context *data_ov005_0205b80c;
extern int func_ov005_0204e0d0(void *,int);
extern void func_ov005_0204e33c(void *,int);
void func_ov005_02053250(void) {
    int entry;
    if(data_ov005_0205b80c->interactiveEntriesInitialized)return;
    entry=func_ov005_0204e0d0(data_ov005_0205b80c->embeddedManager,1);
    func_ov005_0204e33c(data_ov005_0205b80c->embeddedManager,entry);
    entry=func_ov005_0204e0d0(data_ov005_0205b80c->embeddedManager,29);
    func_ov005_0204e33c(data_ov005_0205b80c->embeddedManager,entry);
    data_ov005_0205b80c->interactiveEntriesInitialized=1;
}
