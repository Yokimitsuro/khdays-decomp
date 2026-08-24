typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Fx32Pair {
    int x;
    int y;
} Fx32Pair;

typedef struct SpriteManagerInit {
    void *resource;
    int enabled;
    int reserved0;
    int reserved1;
} SpriteManagerInit;

typedef struct Ov004Context {
    u8 pad_0000[0x5544];
    void *objects[3];
} Ov004Context;

extern Ov004Context *data_ov004_02051384;
extern void *data_ov004_02051300[];
extern char data_ov004_02051328[];
extern char data_ov004_02051340[];
extern char data_ov004_020510b0[];

extern void func_0202a634(void *object, void *resource, int mode, int style);
extern void func_0202afc4(void *object, int enabled);
extern void func_ov004_020506cc(void *object);
extern void func_02023c60(void *object);
extern void func_02032388(void *manager, SpriteManagerInit *init);
extern void *WM_EndKeySharing_0x02032444(void *manager, int index, int arg);
extern void func_02032800(void *manager, void *object, int arg);
extern void func_0203257c(void *manager, void *object, Fx32Pair *position);
extern void func_020326cc(void *manager, void *object);
extern void func_020326f0(void *manager, void *object, int arg, int scale);
extern void func_02032760(void *manager, void *object, int arg);
extern void func_02032798(void *manager, int value);
extern void func_02032838(void *manager, int enabled);
extern void func_020327e0(void *manager, int value);
extern void func_0202f7fc(void *textEngine, void *resource);
extern void func_0202f834(void *tileEngine, int layer, void *textEngine, u16 *rect);
extern void GX_LoadBGPltt(void *src, int offset, u32 size);

void func_ov004_0204fd60(void) {
    Fx32Pair position;
    SpriteManagerInit init;
    u16 rect[8];
    int i;
    int offset;
    void *object;

    i = 0;
    offset = i;
    for (; i < 10; i++) {
        func_0202a634((char *)data_ov004_02051384 + offset,
                      data_ov004_02051300[i], 0, 14);
        func_0202afc4((char *)data_ov004_02051384 + offset, 1);
        offset += 0x108;
    }

    func_ov004_020506cc(*(void **)((char *)data_ov004_02051384 + 0x5568));
    func_02023c60((char *)data_ov004_02051384 + 0xac0);
    *(int *)((char *)data_ov004_02051384 + 0x55ec) = 0;

    init.resource = data_ov004_02051328;
    init.enabled = 1;
    init.reserved0 = 0;
    init.reserved1 = 0;
    func_02032388((char *)data_ov004_02051384 + 0xb0c, &init);

    for (i = 0; i < 3; i++) {
        object = WM_EndKeySharing_0x02032444((char *)data_ov004_02051384 + 0xb0c, i, 0);
        data_ov004_02051384->objects[i] = object;
        func_02032800((char *)data_ov004_02051384 + 0xb0c,
                      data_ov004_02051384->objects[i], 0);

        switch (i) {
        case 0:
            position.x = 0x80000;
            position.y = 0x78000;
            *(int *)((char *)data_ov004_02051384 + 0x5588) = 0x78000;
            func_0203257c((char *)data_ov004_02051384 + 0xb0c,
                          data_ov004_02051384->objects[i],
                          &position);
            func_020326cc((char *)data_ov004_02051384 + 0xb0c,
                          data_ov004_02051384->objects[i]);
            func_02032760((char *)data_ov004_02051384 + 0xb0c,
                          data_ov004_02051384->objects[i], 0);
            break;
        case 1:
            position.x = 0x80000;
            position.y = 0x60000;
            *(int *)((char *)data_ov004_02051384 + 0x557c) = 0;
            *(int *)((char *)data_ov004_02051384 + 0x5580) = 0x171;
            func_0203257c((char *)data_ov004_02051384 + 0xb0c,
                          data_ov004_02051384->objects[i],
                          &position);
            func_020326f0((char *)data_ov004_02051384 + 0xb0c,
                          data_ov004_02051384->objects[i],
                          *(int *)((char *)data_ov004_02051384 + 0x557c), 0x1000);
            func_02032760((char *)data_ov004_02051384 + 0xb0c,
                          data_ov004_02051384->objects[i], 0);
            break;
        case 2:
            position.x = 0x64000;
            position.y = 0x58000;
            func_0203257c((char *)data_ov004_02051384 + 0xb0c,
                          data_ov004_02051384->objects[i],
                          &position);
            func_02032760((char *)data_ov004_02051384 + 0xb0c,
                          data_ov004_02051384->objects[i], 0);
            break;
        }
    }

    func_02032798((char *)data_ov004_02051384 + 0xb0c, 0x2f);
    func_02032838((char *)data_ov004_02051384 + 0xb0c, 1);
    func_020327e0((char *)data_ov004_02051384 + 0xb0c, 0);

    func_0202f7fc((char *)data_ov004_02051384 + 0x55a0, data_ov004_02051340);

    rect[0] = 0;
    rect[4] = 0;
    rect[5] = 0;
    rect[6] = 0;
    rect[7] = 0;
    rect[1] = 11;
    rect[2] = 0x20;
    rect[3] = 6;
    func_0202f834((char *)data_ov004_02051384 + 0x55ac, 3,
                  (char *)data_ov004_02051384 + 0x55a0, rect);

    GX_LoadBGPltt(data_ov004_020510b0, 0, 8);
}

