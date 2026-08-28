typedef void (*Ov002OverlayHook)(void);
typedef unsigned int FSOverlayID;

extern unsigned int OVERLAY_25_ID[1];
extern unsigned int OVERLAY_26_ID[1];
extern unsigned int OVERLAY_27_ID[1];
#define FS_OVERLAY_ID_ov025 ((FSOverlayID)(unsigned int)&OVERLAY_25_ID)
#define FS_OVERLAY_ID_ov026 ((FSOverlayID)(unsigned int)&OVERLAY_26_ID)
#define FS_OVERLAY_ID_ov027 ((FSOverlayID)(unsigned int)&OVERLAY_27_ID)

typedef struct {
    unsigned char pad0000[0x8b50];
    int nOverlayId;
    unsigned char pad8b54[0x28];
    Ov002OverlayHook pOverlayHook;
} Ov002RootContext;

extern Ov002RootContext *data_ov002_0207fa00;
extern void func_0201e470(int processor, int overlayId);
extern void func_ov025_02082be0(Ov002OverlayHook *hook);
extern void func_ov026_02082b4c(Ov002OverlayHook *hook);
extern void func_ov027_02083dbc(Ov002OverlayHook *hook);

/* Brings up the sub-flow overlay a kind asks for, then runs the entry point it
 * left behind.
 *
 * Three of the six kinds share ov025, one takes ov026 and one ov027; the
 * remaining one loads nothing.  Each case stamps the overlay id into the root
 * first, loads it, and hands the overlay the address of the hook slot to fill
 * in.  The hook is then called whichever way the switch went, so the kind that
 * loads nothing simply re-runs whatever was already there.
 *
 * The arms are written 8/11/13, 12, 9 because that is the order the ROM lays
 * their blocks down after the jump table.
 */
void func_ov002_0206a4d4(int nKind)
{
    Ov002RootContext *root = data_ov002_0207fa00;

    switch (nKind) {
    case 8:
    case 11:
    case 13:
        root->nOverlayId = FS_OVERLAY_ID_ov025;
        func_0201e470(0, root->nOverlayId);
        func_ov025_02082be0(&root->pOverlayHook);
        break;
    case 12:
        root->nOverlayId = FS_OVERLAY_ID_ov026;
        func_0201e470(0, root->nOverlayId);
        func_ov026_02082b4c(&root->pOverlayHook);
        break;
    case 9:
        root->nOverlayId = FS_OVERLAY_ID_ov027;
        func_0201e470(0, root->nOverlayId);
        func_ov027_02083dbc(&root->pOverlayHook);
        break;
    }
    root->pOverlayHook();
}
