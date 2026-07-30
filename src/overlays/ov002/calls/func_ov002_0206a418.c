typedef void (*Ov002OverlayHook)(void);
typedef unsigned int FSOverlayID;

extern unsigned int OVERLAY_23_ID[1];
#define FS_OVERLAY_ID_ov023 ((FSOverlayID)(unsigned int)&OVERLAY_23_ID)

typedef struct {
    unsigned char pad0000[0x8b50];
    int nOverlayId;
    unsigned char pad8b54[0x28];
    Ov002OverlayHook pOverlayHook;
} Ov002RootContext;

extern Ov002RootContext *data_ov002_0207fa00;
extern void func_0201e470(int processor, int overlayId);
extern void func_ov023_02082cc0(Ov002OverlayHook *hook);

void func_ov002_0206a418(void)
{
    Ov002RootContext *root = data_ov002_0207fa00;

    root->nOverlayId = FS_OVERLAY_ID_ov023;
    func_0201e470(0, root->nOverlayId);
    func_ov023_02082cc0(&root->pOverlayHook);
    root->pOverlayHook();
}
