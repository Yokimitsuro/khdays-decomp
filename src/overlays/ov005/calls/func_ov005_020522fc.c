typedef struct UiLayoutPos { int x,y; } UiLayoutPos;
typedef struct Ov005Context { char header[0x54]; char embeddedManager[0x4a80]; } Ov005Context;
extern Ov005Context *data_ov005_0205b80c;
extern int func_ov005_0204e0d0(void *,int);
extern void func_ov005_0204e1e0(void *,int,const UiLayoutPos *);
void func_ov005_020522fc(int entryId,short x,short y) {
    UiLayoutPos offset;
    int slot;
    offset.x=x<<12;
    offset.y=y<<12;
    slot=func_ov005_0204e0d0(data_ov005_0205b80c->embeddedManager,entryId);
    func_ov005_0204e1e0(data_ov005_0205b80c->embeddedManager,slot,&offset);
}
