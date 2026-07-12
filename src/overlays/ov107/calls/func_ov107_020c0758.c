/* Two-step teardown: FS_EndOverlay(param_1) then FS_UnloadOverlayImage(param_1). */
extern void FS_EndOverlay(int arg);
extern void FS_UnloadOverlayImage(int arg);
void func_ov107_020c0758(int param_1) {
    FS_EndOverlay(param_1);
    FS_UnloadOverlayImage(param_1);
}
