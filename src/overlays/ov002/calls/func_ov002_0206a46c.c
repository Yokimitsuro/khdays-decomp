typedef void (*Ov002OverlayHook)(void);
typedef unsigned int FSOverlayID;

extern unsigned int OVERLAY_24_ID[1];
#define FS_OVERLAY_ID_ov024 ((FSOverlayID)(unsigned int)&OVERLAY_24_ID)

typedef struct {
    unsigned char pad0000[0x8b50];
    int nOverlayId;
    unsigned char pad8b54[0x28];
    Ov002OverlayHook pOverlayHook;
} Ov002RootContext;

extern Ov002RootContext *data_ov002_0207fa00;
extern void func_0201e470(int processor, int overlayId);
extern void func_ov024_020832c4(Ov002OverlayHook *hook);

void func_ov002_0206a46c(void)
{
    Ov002RootContext *root = data_ov002_0207fa00;

    root->nOverlayId = FS_OVERLAY_ID_ov024;
    func_0201e470(0, root->nOverlayId);
    func_ov024_020832c4(&root->pOverlayHook);
    root->pOverlayHook();
}
