extern int FS_EndOverlay();

int FS_UnloadOverlayImage(void) {
    FS_EndOverlay();
    return 1;
}
