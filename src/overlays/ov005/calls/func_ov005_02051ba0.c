typedef unsigned short u16;
typedef struct Ov005MenuItemHeader {char data[0x24c];} Ov005MenuItemHeader;
extern char *data_ov005_0205b80c;
extern void func_ov005_0205192c(Ov005MenuItemHeader *,unsigned int,int,int);
void func_ov005_02051ba0(unsigned int itemId) {
    func_ov005_0205192c((Ov005MenuItemHeader *)(data_ov005_0205b80c+0x4c98)+itemId,(u16)itemId,1,itemId==1?1:0);
}
