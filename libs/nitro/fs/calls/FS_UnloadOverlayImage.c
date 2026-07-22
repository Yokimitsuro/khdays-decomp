/* Ends the overlay and always reports success. */
extern void FS_EndOverlay(void *p);

int FS_UnloadOverlayImage(void *p) {
    FS_EndOverlay(p);
    return 1;
}
