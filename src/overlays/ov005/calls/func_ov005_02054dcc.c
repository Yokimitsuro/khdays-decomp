typedef unsigned char u8;
typedef unsigned short u16;
typedef struct TouchPoint {u16 x,y,valid,flags;} TouchPoint;
typedef struct Vec2Fx32 {int x,y;} Vec2Fx32;
typedef struct Ov005SpriteManager {char opaque[0x4a44];TouchPoint touchPoint;char tail[0x34];} Ov005SpriteManager;
typedef struct Ov005SelectionState {
    signed char selectedItem,activeRow,firstVisibleItem;
    char opaque03;
    int maxFirstVisibleItem,cachedRowItemCounts[2],scrollThumbHeight;
} Ov005SelectionState;
typedef struct Ov005Context {
    char opaque00[0x54];
    Ov005SpriteManager embeddedManager;
    char opaque4ad4[0x11c];
    int menuState;
    char opaque4bf4[8];
    Ov005SelectionState selection;
} Ov005Context;
typedef struct Ov005ScrollTouchFrame {int pixelX,pixelY;TouchPoint touch;} Ov005ScrollTouchFrame;
extern Ov005Context *data_ov005_0205b80c;
extern TouchPoint *func_ov005_0204e4a0(Ov005SpriteManager *,TouchPoint *);
extern void *func_ov005_0204e0d0(Ov005SpriteManager *,int);
extern Vec2Fx32 *func_ov005_0204e1d8(Ov005SpriteManager *,void *);
/* Signed division runtime: quotient in r0, remainder in r1; only quotient is used. */
extern long long func_02020400(int numerator,int denominator);
void func_ov005_02054dcc(void) {
    Ov005SelectionState *selection=&data_ov005_0205b80c->selection;
    Ov005ScrollTouchFrame frame;
    Vec2Fx32 *position;
    int trackY;
    u8 index;
    if(data_ov005_0205b80c->menuState<=1)return;
    func_ov005_0204e4a0(&data_ov005_0205b80c->embeddedManager,&frame.touch);
    position=func_ov005_0204e1d8(&data_ov005_0205b80c->embeddedManager,func_ov005_0204e0d0(&data_ov005_0205b80c->embeddedManager,4));
    {
        /* Isolate the X read to preserve the original conversion register allocation. */
        int x=*(volatile int*)&position->x,y=position->y;
        frame.pixelX=x>>12;
        frame.pixelY=trackY=y>>12;
    }
    if(frame.touch.y<trackY)return;
    if(frame.touch.y>trackY+112)return;
    for(index=0;index<=selection->maxFirstVisibleItem;index++) {
        int quotient=(int)func_02020400(112,selection->maxFirstVisibleItem+1);
        if(trackY+quotient*index<frame.touch.y)selection->firstVisibleItem=index;
    }
}
