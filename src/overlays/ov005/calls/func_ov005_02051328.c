typedef unsigned short u16;
typedef struct NNSFndList {void *head,*tail;u16 count,offset;} NNSFndList;
typedef struct Ov005PanelView {char opaque[0x20];NNSFndList itemQuantities;char tail[0x100-0x2c];} Ov005PanelView;
typedef struct Ov005ItemQuantity {int itemId,quantity;} Ov005ItemQuantity;
typedef struct PlayerItemLimit {u16 itemId;short limit;} PlayerItemLimit;
extern char *data_0204be18;
extern void NNS_FndInitList(NNSFndList *,u16);
extern void *NNS_FndGetNextListObject(NNSFndList *,void *);
extern void func_ov005_020506a4(Ov005PanelView *,void *);
extern void func_ov005_020509ac(Ov005PanelView *,void **,NNSFndList *,u16 *);
extern void func_ov005_02050730(Ov005PanelView *,void **,NNSFndList *);
extern unsigned int func_02030788(void);
extern PlayerItemLimit *func_0203583c(int,unsigned int);
extern void func_ov005_0205129c(unsigned int,int);
extern void func_ov005_02050bfc(Ov005PanelView *,void **,NNSFndList *);
/* Historical symbol name; this is the ov005 panel cleanup veneer, not WM code. */
extern void WM_EndKeySharing_0x02050724(Ov005PanelView *);
void func_ov005_02051328(void) {
    void *entries[120];
    Ov005PanelView view;
    NNSFndList nodes;
    Ov005ItemQuantity *item;
    NNS_FndInitList(&nodes,0x28);
    func_ov005_020506a4(&view,0);
    func_ov005_020509ac(&view,entries,&nodes,(u16 *)(data_0204be18+0xee0));
    func_ov005_02050730(&view,entries,&nodes);
    for(item=NNS_FndGetNextListObject(&view.itemQuantities,0);item;item=NNS_FndGetNextListObject(&view.itemQuantities,item)) {
        int id=item->itemId;
        if (id>=2 && id<=11) {
            PlayerItemLimit *limit=func_0203583c(func_02030788(),id);
            int excess;
            if (limit==0) excess=item->quantity;
            else excess=item->quantity-limit->limit;
            if(excess>0)func_ov005_0205129c(item->itemId,excess);
        }
    }
    func_ov005_02050bfc(&view,entries,&nodes);
    WM_EndKeySharing_0x02050724(&view);
}
