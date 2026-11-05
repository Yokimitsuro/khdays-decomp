#include "game/class_descriptor.h"
/* main .data, 0x0204252c-0x020425ec: the root task descriptor main() instantiates (BootTask,
 * 02020928 / 02020974) and the scene table the scene switcher 0202099c indexes by scene id: each
 * row names the overlay to load (-1 = none) and the InstantiateClass descriptor of the scene task
 * inside it. Seen running: 1 is the logos, the title, all its menus and the save-file screen
 * (ov000); 2 the field (ov002); 5 the day title card (ov004); 6 the results screen of a Mission
 * Mode mission (ov005); 7 the Mission Mode character select (ov006); 10 Roxas's narration after
 * the clock-tower cutscene of day 255 (ov007), which Story Mode follows with 5 (the next day's
 * title card) and 2; 11 the opening movie that follows "new game" in Story Mode (ov012); 19 the
 * mission lobby (ov008).
 *
 * Leaving a mission: START in the field (2) opens the pause menu; retiring and confirming fades to
 * black, still in scene 2, until A is pressed; scene 6 then shows the mission as cancelled, and
 * closing it returns to the lobby (19).
 */
typedef struct SceneEntry {
    int overlayId;            /* 0x00: overlay to load, -1 = none */
    void *classDesc;          /* 0x04: InstantiateClass descriptor */
} SceneEntry;

extern void Boot_InitScene(void);   /* BootTask_Construct */
extern void func_02020974(void);
extern int gMainHeap;          /* the main heap arena */
extern int gOv000TitleSceneClass, gOv002FieldSceneClass, data_ov003_0204f8e4, gOv004CalendarSceneClass,
           gOv005MissionResultSceneClass, gOv006MissionSelectSceneClass, data_ov011_0205e8a0, data_ov006_02056220,
           gOv007MonologueSceneClass, gOv012OpeningSceneClass, gOv010ConnectionErrorSceneClass, gOv008MissionCampSceneClass;

/* Two words ov107 020c6624 reads. */
int data_0204252c = 1;
int data_02042530 = 5;

/* The root task: class 0 / group 0xf, an 8-byte state block on the main arena. */
GameClassDescriptor gBootTaskClass = {
    0,     /* nClassId */
    0xf,   /* nGroupId */
    Boot_InitScene,  /* pfnCtor */
    func_02020974,  /* pfnMethod */
    8,     /* nAuxSize */
    &gMainHeap,  /* pArena */
};

SceneEntry gSceneTable[20] = {
    { -1, 0 },                        /* 0 */
    { 0, &gOv000TitleSceneClass },      /* 1: logos, title, menus, save files (ov000) */
    { 2, &gOv002FieldSceneClass },      /* 2: field (ov002) */
    { 3, &data_ov003_0204f8e4 },      /* 3 */
    { -1, 0 },                        /* 4 */
    { 4, &gOv004CalendarSceneClass },      /* 5: day title card (ov004) */
    { 5, &gOv005MissionResultSceneClass },      /* 6: mission results (ov005) */
    { 6, &gOv006MissionSelectSceneClass },      /* 7: mission-mode character select (ov006) */
    { 11, &data_ov011_0205e8a0 },     /* 8 */
    { 9, &data_ov006_02056220 },      /* 9: the descriptor at 0x02056220 inside ov009 (the delink names the address after ov006) */
    { 7, &gOv007MonologueSceneClass },      /* 10: Roxas's monologue after the clock-tower scene (ov007) */
    { 12, &gOv012OpeningSceneClass },     /* 11: opening movie (ov012) */
    { 10, &gOv010ConnectionErrorSceneClass },     /* 12: the connection-error screen (ov010) */
    { -1, 0 },                        /* 13 */
    { -1, 0 },                        /* 14 */
    { -1, 0 },                        /* 15 */
    { -1, 0 },                        /* 16 */
    { -1, 0 },                        /* 17 */
    { -1, 0 },                        /* 18 */
    { 8, &gOv008MissionCampSceneClass },      /* 19: Mission Mode's camp (ov008) */
};

/* A byte flag (0xff = unset) the pause / dialog helpers 02020cf8..02022410 read. */
int data_020425e8 = 0xff;
