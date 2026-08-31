typedef unsigned char u8;
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
extern int func_ov005_0204e0d0(void *,int);
extern void *func_ov005_0204e1d8(void *,int);
extern void func_ov005_020522fc(int,short,short);
extern int func_02020400(int numerator,int denominator);
static inline int GetScrollOffset(Ov005SelectionState *selection) {
    if(selection->maxFirstVisibleItem==0)return 0;
    return func_02020400((112-selection->scrollThumbHeight)*selection->firstVisibleItem,selection->maxFirstVisibleItem);
}
void func_ov005_02053a74(void) {
    Ov005Context *context=data_ov005_0205b80c;
    Ov005SelectionState *selection=&context->selection;
    u8 count=(selection->scrollThumbHeight-32)/8;
    short y=(short)GetScrollOffset(selection);
    u8 i;
    int entry;
    entry=func_ov005_0204e0d0(context->embeddedManager,5);
    func_ov005_0204e1d8(data_ov005_0205b80c->embeddedManager,entry);
    func_ov005_020522fc(4,0,(short)y);
    func_ov005_020522fc(30,0,(short)y);
    for(i=0;i<count;i++) {
        func_ov005_020522fc(i+6,0,(short)y);
        func_ov005_020522fc(i+32,0,(short)y);
    }
    func_ov005_020522fc(5,0,y+count*8);
    func_ov005_020522fc(31,0,y+count*8);
}
