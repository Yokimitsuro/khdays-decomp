typedef void (*Ov005MenuStateHandler)(void);
typedef struct Ov005MenuStateTable { Ov005MenuStateHandler states[9]; } Ov005MenuStateTable;
typedef struct Ov000ResourceTracker { char opaque[76]; } Ov000ResourceTracker;
typedef struct Ov005SpriteManager { char opaque[0x4a80]; } Ov005SpriteManager;
typedef struct MenuLimitHeader { char opaque[26]; } MenuLimitHeader;
typedef struct Ov005Context {
    char header[8];
    Ov000ResourceTracker resourceTracker;
    Ov005SpriteManager embeddedManager;
    char opaque4ad4[0x11c];
    int menuState;
    char opaque4bf4[0x1e];
    MenuLimitHeader menuLimitHeader;
} Ov005Context;
extern const Ov005MenuStateTable data_ov005_0205b368;
extern Ov005Context *data_ov005_0205b80c;
extern int FS_UnloadOverlayImage_0x020362ec(MenuLimitHeader *);
extern void func_ov005_0204d110(Ov000ResourceTracker *);
extern void func_ov005_0204dd18(Ov005SpriteManager *,int);
extern void FX_Inv_0x020522ec(void);
extern void func_ov005_02053e44(void);
void *func_ov005_02053d74(void) {
    Ov005MenuStateTable handlers=data_ov005_0205b368;
    FS_UnloadOverlayImage_0x020362ec(&data_ov005_0205b80c->menuLimitHeader);
    func_ov005_0204d110(&data_ov005_0205b80c->resourceTracker);
    func_ov005_0204dd18(&data_ov005_0205b80c->embeddedManager,0);
    handlers.states[data_ov005_0205b80c->menuState]();
    if(data_ov005_0205b80c->menuState>1)FX_Inv_0x020522ec();
    func_ov005_02053e44();
    return 0;
}
