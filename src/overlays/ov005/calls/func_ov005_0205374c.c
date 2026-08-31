typedef unsigned char u8;
typedef struct Ov005SelectionState {
    u8 unknown00,activeRow,firstVisibleItem,unknown03;
    int maxFirstVisibleItem,cachedRowItemCounts[2],scrollThumbHeight;
} Ov005SelectionState;
typedef struct Ov005Context {
    char header[0x54];
    char embeddedManager[0x4a80];
    char opaque4ad4[0x128];
    Ov005SelectionState selection;
    char opaque4c10[0x30];
    int scrollCapVisible[2];
    int scrollSegmentVisible[11];
} Ov005Context;
extern Ov005Context *data_ov005_0205b80c;
extern int func_ov005_020533a8(void);
extern int func_ov005_0204e0d0(void *,int);
extern void *func_ov005_0204e1d8(void *,int);
extern void func_ov005_0204e29c(void *,int,int);
extern void func_ov005_020522fc(int,short,short);
void func_ov005_0205374c(void) {
    Ov005SelectionState *selection=&data_ov005_0205b80c->selection;
    u8 i,count;
    int slot,visible;
    selection->scrollThumbHeight=(func_ov005_020533a8()*112/100)/8*8;
    if(selection->scrollThumbHeight<32) selection->scrollThumbHeight=32;
    count=(selection->scrollThumbHeight-32)/8;
    slot=func_ov005_0204e0d0(data_ov005_0205b80c->embeddedManager,5);
    func_ov005_0204e1d8(data_ov005_0205b80c->embeddedManager,slot);
    slot=func_ov005_0204e0d0(data_ov005_0205b80c->embeddedManager,4);
    func_ov005_0204e29c(data_ov005_0205b80c->embeddedManager,slot,1);
    slot=func_ov005_0204e0d0(data_ov005_0205b80c->embeddedManager,5);
    func_ov005_0204e29c(data_ov005_0205b80c->embeddedManager,slot,1);
    data_ov005_0205b80c->scrollCapVisible[0]=data_ov005_0205b80c->scrollCapVisible[1]=1;
    for(i=0;i<11;i++) {
        visible=i<count?1:0;
        slot=func_ov005_0204e0d0(data_ov005_0205b80c->embeddedManager,i+6);
        func_ov005_0204e29c(data_ov005_0205b80c->embeddedManager,slot,visible);
        data_ov005_0205b80c->scrollSegmentVisible[i]=visible;
    }
    func_ov005_020522fc(5,0,count*8);
    func_ov005_020522fc(31,0,count*8);
}
