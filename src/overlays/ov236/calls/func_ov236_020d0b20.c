typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u16 soundId;
    u16 parameter;
} Ov236Cue;

typedef struct {
    u16 pad_0000[4];
    Ov236Cue surprisedCue;
} Ov236CueTable;

typedef struct Ov236CueObject Ov236CueObject;
typedef void (*Ov236CueCallback)(Ov236CueObject *object, Ov236Cue *cue, int size);

struct Ov236CueObject {
    u8 pad_0000[0x24];
    Ov236CueCallback playCue;
};

typedef struct {
    Ov236CueObject *object;
} Ov236Node;

typedef struct {
    u8 pad_0000[4];
    Ov236Node *node;
    u8 pad_0008[0x20 - 8];
    s8 scriptSlot;
} Ov236Actor;

extern void func_ov107_020c9264(Ov236CueObject *object, int mode, int flag);
extern void func_0203c634(Ov236Actor *self, int index, void *callback);
extern Ov236CueTable data_ov236_020d63c0;
extern void func_ov236_020d0b88(void);

void func_ov236_020d0b20(Ov236Actor *self) {
    Ov236Node *node = self->node;
    Ov236Cue cue;
    Ov236CueCallback playCue;

    cue = data_ov236_020d63c0.surprisedCue;
    playCue = node->object->playCue;
    if (playCue != 0) {
        playCue(node->object, &cue, sizeof(cue));
    }
    func_ov107_020c9264(node->object, 0xd, 0);
    func_0203c634(self, self->scriptSlot, &func_ov236_020d0b88);
}
