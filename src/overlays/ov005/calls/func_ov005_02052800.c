typedef unsigned char u8;
typedef unsigned short u16;
typedef struct Ov005MenuItemHeader {u16 itemId;char pad2[0x246];u8 quantities[2];u16 quantityLimit;} Ov005MenuItemHeader;
typedef struct Ov005Context {char pad0[0x4c98];Ov005MenuItemHeader firstMenuItem[636];Ov005MenuItemHeader *firstItemSlot[2][636];} Ov005Context;
extern Ov005Context *data_ov005_0205b80c;
extern void MI_CpuFill8(void *,u8,unsigned int);
void func_ov005_02052800(int *rowCounts) {
    int rowIndex;
    int itemIndex;
    int count;
    MI_CpuFill8(data_ov005_0205b80c->firstItemSlot,0,0x13e0);
    for(rowIndex=0;rowIndex<2;rowIndex++) {
        count=0;
        for(itemIndex=0;itemIndex<636;itemIndex++) {
            if(data_ov005_0205b80c->firstMenuItem[itemIndex].itemId && data_ov005_0205b80c->firstMenuItem[itemIndex].quantities[rowIndex]) {
                data_ov005_0205b80c->firstItemSlot[rowIndex][count]=&data_ov005_0205b80c->firstMenuItem[itemIndex];
                count++;
            }
        }
        rowCounts[rowIndex]=count;
    }
}
