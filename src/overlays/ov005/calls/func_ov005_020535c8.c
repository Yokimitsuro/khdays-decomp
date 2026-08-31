typedef struct Ov005SelectionState {
    signed char selectedItem,activeRow,firstVisibleItem,unknown03;
    int maxFirstVisibleItem,cachedRowItemCounts[2],scrollThumbHeight;
} Ov005SelectionState;
typedef struct Ov005Context {
    char header[0x54];
    char embeddedManager[0x4a80];
    char opaque4ad4[0x128];
    Ov005SelectionState selection;
} Ov005Context;
extern Ov005Context *data_ov005_0205b80c;
extern void func_ov005_020522fc(int,short,short);
extern int func_ov005_0204e0d0(void *,int);
extern void func_ov005_0204e29c(void *,int,int);
extern void func_ov005_02053a74(void);
void func_ov005_020535c8(void) {
    Ov005Context *context=data_ov005_0205b80c;
    Ov005SelectionState *selection=&context->selection;
    int entry;
    func_ov005_020522fc(1,selection->activeRow*112,selection->selectedItem*16);
    func_ov005_020522fc(29,selection->activeRow*112,selection->selectedItem*16);
    if(selection->cachedRowItemCounts[0]!=0 || selection->cachedRowItemCounts[1]!=0) {
        entry=func_ov005_0204e0d0(data_ov005_0205b80c->embeddedManager,1);
        func_ov005_0204e29c(data_ov005_0205b80c->embeddedManager,entry,1);
    } else {
        entry=func_ov005_0204e0d0(data_ov005_0205b80c->embeddedManager,1);
        func_ov005_0204e29c(data_ov005_0205b80c->embeddedManager,entry,0);
    }
    func_ov005_02053a74();
}
