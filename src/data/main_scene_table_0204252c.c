/* main .data, 0x0204252c-0x020425ec: the root task descriptor main() instantiates (BootTask,
 * 02020928 / 02020974) and the scene table the scene switcher 0202099c indexes by scene id: each
 * row names the overlay to load (-1 = none) and the InstantiateClass descriptor of the scene task
 * inside it. Scene 1 is the title (ov000), 7 the mission-mode character select (ov006), 19 the
 * mission map (ov008).
 */
typedef void (*GameClassFn)(void);

typedef struct GameClassDescriptor {
    unsigned short nClassId;  /* 0x00 */
    unsigned short nGroupId;  /* 0x02 */
    GameClassFn pfnCtor;      /* 0x04: returns the object's first state fn */
    GameClassFn pfnMethod;    /* 0x08 */
    int nAuxSize;             /* 0x0c: zero-filled state block */
    int *pArena;              /* 0x10 */
} GameClassDescriptor;

typedef struct SceneEntry {
    int overlayId;            /* 0x00: overlay to load, -1 = none */
    void *classDesc;          /* 0x04: InstantiateClass descriptor */
} SceneEntry;

extern void func_02020928(void);   /* BootTask_Construct */
extern void func_02020974(void);
extern int data_0204c024;          /* the main heap arena */
extern int data_ov000_0205a9c0, data_ov002_0207ef54, data_ov003_0204f8e4, data_ov004_02051210,
           data_ov005_0205b4dc, data_ov006_020565c0, data_ov011_0205e8a0, data_ov006_02056220,
           data_ov007_0204d3c4, data_ov012_0205c2bc, data_ov010_0204cfa0, data_ov008_0208ffa0;

/* Two words ov107 020c6624 reads. */
int data_0204252c = 1;
int data_02042530 = 5;

/* The root task: class 0 / group 0xf, an 8-byte state block on the main arena. */
GameClassDescriptor data_02042534 = {
    0,     /* nClassId */
    0xf,   /* nGroupId */
    func_02020928,  /* pfnCtor */
    func_02020974,  /* pfnMethod */
    8,     /* nAuxSize */
    &data_0204c024,  /* pArena */
};

SceneEntry data_02042548[20] = {
    { -1, 0 },                        /* 0 */
    { 0, &data_ov000_0205a9c0 },      /* 1: title / menus (ov000) */
    { 2, &data_ov002_0207ef54 },      /* 2: field (ov002) */
    { 3, &data_ov003_0204f8e4 },      /* 3 */
    { -1, 0 },                        /* 4 */
    { 4, &data_ov004_02051210 },      /* 5 */
    { 5, &data_ov005_0205b4dc },      /* 6 */
    { 6, &data_ov006_020565c0 },      /* 7: mission-mode character select (ov006) */
    { 11, &data_ov011_0205e8a0 },     /* 8 */
    { 9, &data_ov006_02056220 },      /* 9: the descriptor at 0x02056220 inside ov009 (the delink names the address after ov006) */
    { 7, &data_ov007_0204d3c4 },      /* 10 */
    { 12, &data_ov012_0205c2bc },     /* 11 */
    { 10, &data_ov010_0204cfa0 },     /* 12 */
    { -1, 0 },                        /* 13 */
    { -1, 0 },                        /* 14 */
    { -1, 0 },                        /* 15 */
    { -1, 0 },                        /* 16 */
    { -1, 0 },                        /* 17 */
    { -1, 0 },                        /* 18 */
    { 8, &data_ov008_0208ffa0 },      /* 19: mission map (ov008) */
};

/* A byte flag (0xff = unset) the pause / dialog helpers 02020cf8..02022410 read. */
int data_020425e8 = 0xff;
