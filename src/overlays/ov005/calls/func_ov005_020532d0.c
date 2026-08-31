typedef unsigned char u8;
typedef struct Ov005Context {
    char opaque[0x4bfc];
    u8 unknown4bfc,activeRow,firstVisibleItem,unknown4bff;
    int maxFirstVisibleItem;
    int cachedRowItemCounts[2];
    int scrollThumbHeight;
} Ov005Context;
extern Ov005Context *data_ov005_0205b80c;
extern void MI_CpuFill8(void *,int,unsigned int);
extern void func_ov005_0205374c(void);
void func_ov005_020532d0(int *rowItemCounts) {
    u8 row;
    MI_CpuFill8(&data_ov005_0205b80c->unknown4bfc,0,20);
    for(row=0;row<2;row++) {
        data_ov005_0205b80c->cachedRowItemCounts[row]=rowItemCounts[row];
        if(data_ov005_0205b80c->maxFirstVisibleItem<rowItemCounts[row]-7)
            data_ov005_0205b80c->maxFirstVisibleItem=rowItemCounts[row]-7;
    }
    if(data_ov005_0205b80c->cachedRowItemCounts[0]==0 && data_ov005_0205b80c->cachedRowItemCounts[1]!=0)
        data_ov005_0205b80c->activeRow=1;
    func_ov005_0205374c();
}
