extern void GFXi_EnqueueCommand(int cmd, int a, int b, int c);
/* Enqueue GX command 9 with the display-list pointer at obj+0x54 (+0xc) and its length (+8). */
void func_ov027_02083cb8(int obj) {
    GFXi_EnqueueCommand(9, 0, *(int *)(obj + 0x54) + 0xc, *(int *)(*(int *)(obj + 0x54) + 8));
}
