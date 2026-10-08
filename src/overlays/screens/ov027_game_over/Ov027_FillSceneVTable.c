/* Fills the game over scene's interface table. */

extern void Ov027_SetupGraphics(void);
extern void Ov027_CreateSceneTask(void);
extern void Ov027_DestroySceneTask(void);
extern void Ov027_SceneActivate(void);
extern void Ov027_SetFlag4(void);
extern void Ov027_SceneIsActive(void);
extern void Ov027_SceneIsIdle(void);
extern void Ov027_SceneGetField24(void);

/* Fills in the scene's vtable. */
void Ov027_FillSceneVTable(void **vt) {
    vt[0] = (void *)&Ov027_SetupGraphics;
    vt[1] = (void *)&Ov027_CreateSceneTask;
    vt[2] = (void *)&Ov027_DestroySceneTask;
    vt[3] = (void *)&Ov027_SceneActivate;
    vt[4] = (void *)&Ov027_SetFlag4;
    vt[5] = (void *)&Ov027_SceneIsActive;
    vt[6] = (void *)&Ov027_SceneIsIdle;
    vt[7] = 0;
    vt[9] = (void *)&Ov027_SceneGetField24;
    vt[10] = 0;
}
