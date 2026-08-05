/*
 * Ov008_Menu_InitPanelSubObject - set up one menu panel sub-object: register its
 * sprite sequence and load the layout archive that matches the current scene.
 *
 * Called from Ov008_Menu_BindScenePanels once per named panel resource. It stores the
 * resource id / scene id / slot into the panel header, builds a packed resource
 * descriptor from the message-container base (resBase, masked to 4-byte alignment and
 * flagged 0x80000000), registers the sprite sequence (func_0202a634) and primes the
 * panel node, then decides which layout archive variant to load:
 *   - scene 0xe: a fixed archive (data_ov025_020b4c3c);
 *   - scenes {0,5,6,0xb,0x10}: variant 0;
 *   - scenes {4,9,0xf}: variant 0 when slot==3, else variant 1;
 *   - scenes {2,0x13}: variant 0 when slot==1, else variant 1;
 *   - any other scene: nothing (variant stays -1).
 * The chosen archive handle is stored at panel+0x160, wired in via func_0202a3cc, and
 * bit 0x4 of the panel flag byte is set to mark it loaded.
 *
 * The character-flag word (charFlags) gets +0x50 for the same {2,0x13}/{4,9,0xf} scene
 * & slot combinations that select variant 1, before its low bits (0xfffffc>>0xf) are
 * folded into the descriptor.
 *
 * Codegen: both scene switches must emit the {4,9,0xf} body before the {2,0x13} body,
 * and each variant test is written as an if/else (true-branch-first) so mwcc emits
 * `cmp; bne; <=0>; b; <=1>` rather than the ternary's `beq`/reversed layout.
 * Callee arity (Ghidra invents trailing r2/r3 args): func_02016cd0 takes 2 args,
 * func_0202afc4 takes 2, func_0201ef9c (Archive_LoadFile) takes 2.
 */

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

extern void  func_0202a634(void *node, u32 desc, int a, int b);
extern void  func_02016cd0(int list, int a);
extern void  func_0202afc4(void *node, int a);
extern void  func_0202afdc(int node, int a);
extern void *func_0201ef9c(char *name, int kind);
extern void  func_0202a3cc(int a, int b, void *handle, int d);
extern char  data_ov025_020b4c3c[];

void func_ov025_0208c434(u8 *panel, int resBase, int subId, int sceneId, u32 charFlags, int slot)
{
    u32 descriptor;
    int variant;

    panel[2] = (u8)subId;
    panel[3] = (u8)sceneId;
    switch (sceneId) {
    case 4:
    case 9:
    case 0xf:
        if (slot != 3) charFlags += 0x50;
        break;
    case 2:
    case 0x13:
        if (slot != 1) charFlags += 0x50;
        break;
    }
    descriptor = ((resBase + 0x8000) & 0xfffffc) << 7 | 0x80000000;
    func_0202a634((u16 *)(panel + 4), descriptor | (0xfffffc >> 0xf & charFlags), 1, panel[2] + 7);
    func_02016cd0(*(int *)(panel + 0x7c), 0x3f);
    func_0202afc4((u16 *)(panel + 4), 1);
    func_0202afdc((int)(panel + 4), 0x7fff);
    variant = -1;
    switch (sceneId) {
    case 0:
    case 5:
    case 6:
    case 0xb:
    case 0x10:
        variant = 0;
        break;
    case 4:
    case 9:
    case 0xf:
        if (slot == 3) variant = 0; else variant = 1;
        break;
    case 2:
    case 0x13:
        if (slot == 1) variant = 0; else variant = 1;
        break;
    case 0xe:
        *(void **)(panel + 0x160) = func_0201ef9c(data_ov025_020b4c3c, panel[2] + 7);
        func_0202a3cc((int)(panel + 0x13c), (int)(panel + 4), *(void **)(panel + 0x160), panel[2] + 7);
        *panel |= 4;
        break;
    }
    if (variant >= 0) {
        *(void **)(panel + 0x160) = func_0201ef9c((char *)(descriptor | (variant + 0xdcU & 0x1ff)), subId + 7);
        func_0202a3cc((int)(panel + 0x13c), (int)(panel + 4), *(void **)(panel + 0x160), panel[2] + 7);
        *panel |= 4;
    }
    panel[1] = (u8)slot;
}
