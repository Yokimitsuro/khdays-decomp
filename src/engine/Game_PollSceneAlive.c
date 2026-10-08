/* Game_PollSceneAlive -- frame-loop scene gate (called once per frame from GameMain
 * @0x02000d84). data_027e0060 is the current-scene id byte; 0 = no active scene.
 * When a scene is active, returns the ov105 scene-manager "running" flag
 * (Ov105_WH_GetSystemState = sceneMgr->field_0x24). GameMain treats a 0 return as
 * "scene ended" and branches into the transition/teardown path (0x02000e20). */
extern signed char data_027e0060;
extern int Ov105_WH_GetSystemState(void);

int Game_PollSceneAlive(void) {
    if (data_027e0060 == 0) return 0;
    return Ov105_WH_GetSystemState();
}
