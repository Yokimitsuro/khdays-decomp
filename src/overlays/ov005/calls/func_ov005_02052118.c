typedef unsigned char u8;
typedef struct Ov005MenuQuad Ov005MenuQuad;
typedef struct Ov005ListWindow {char opaque[2];signed char firstVisible;} Ov005ListWindow;
typedef struct Ov005MenuItem {char opaque[0x244];int indicatorState;} Ov005MenuItem;
extern char *data_ov005_0205b80c;
extern signed char func_ov005_02053370(int row);
extern void func_ov005_02050e50(void);
extern void func_ov005_02050f9c(Ov005MenuQuad *quad);
extern void func_ov005_02050f98(void);
extern void func_02032710(void *manager,int slot,int visible);
extern void func_020325ec(void *manager,int slot,unsigned int frame);
#define MANAGER (*(void **)(data_ov005_0205b80c+0x4ad4))
#define SLOT(row,index) (*(int *)((char *)((row)*0x1c)+(int)data_ov005_0205b80c+(index)*4+0x62140))
void func_ov005_02052118(void) {
    u8 i;
    Ov005ListWindow *window=(Ov005ListWindow *)(data_ov005_0205b80c+0x4bfc);
    u8 row;
    func_ov005_02050e50();
    for (row=0;row<2;row++) {
        signed char count=func_ov005_02053370(row);
        for (i=0;i<count;i++) {
            func_ov005_02050f9c((Ov005MenuQuad *)(data_ov005_0205b80c+0x61f48+row*0xfc+i*0x24));
            switch ((*(Ov005MenuItem **)((char *)(row*0x9f0)+(int)data_ov005_0205b80c+(window->firstVisible+i)*4+0x60168))->indicatorState) {
            case 0:func_02032710(MANAGER,SLOT(row,i),0);break;
            case 1:func_02032710(MANAGER,SLOT(row,i),1);func_020325ec(MANAGER,SLOT(row,i),0);break;
            case 2:func_02032710(MANAGER,SLOT(row,i),1);func_020325ec(MANAGER,SLOT(row,i),1);break;
            }
        }
        for (;i<7;i++) func_02032710(MANAGER,SLOT(row,i),0);
    }
    func_ov005_02050f98();
}
