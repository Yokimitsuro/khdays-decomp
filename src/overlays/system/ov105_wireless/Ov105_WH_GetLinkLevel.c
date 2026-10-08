/* Interworking tail-call veneer (`ldr ip,[pc] ; bx ip`): forwards to Ov105_WM_GetLinkLevel: WH_GetLinkLevel (wh.c). */
extern void *Ov105_WM_GetLinkLevel();

void *Ov105_WH_GetLinkLevel() {
    return Ov105_WM_GetLinkLevel();
}
