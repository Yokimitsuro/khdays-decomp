typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Ov022LimitConfig {
    char padding000[6];
    u16 limit06;
} Ov022LimitConfig;

typedef struct Ov022RuntimeContext {
    char padding000[0x30];
    void *activeObject30;
} Ov022RuntimeContext;

typedef struct Ov022ActorEntry {
    char padding000[0x12];
    u16 selectedLimit12;
    char padding014[0x4d8];
    void *activeObject4ec;
} Ov022ActorEntry;

typedef struct Ov022RoomState {
    char padding000[0x10];
    void *instance10;
    int overlayId14;
    u8 group18;
    u8 padding019;
    u8 active1a;
} Ov022RoomState;

typedef struct Ov022CreationDescriptor {
    int type00;
    int duplicateType04;
    u8 value08;
    char padding009[3];
    int sessionActive0c;
    int inputValue10;
} Ov022CreationDescriptor;

typedef void *(*Ov022CreateCallback)(Ov022CreationDescriptor *descriptor);

typedef struct Ov022EntrySystem {
    Ov022CreateCallback callback00;
    Ov022RoomState *root04;
    Ov022CreationDescriptor descriptor08;
} Ov022EntrySystem;

typedef union Ov022RootOrEntry {
    Ov022RoomState root;
    Ov022ActorEntry entry;
} Ov022RootOrEntry;

extern Ov022EntrySystem data_ov022_020b2e78;
extern Ov022CreationDescriptor data_ov022_020b2e80;
extern Ov022LimitConfig data_0204c77c;
extern Ov022LimitConfig data_0204c784;

extern int func_ov002_0206e6e8(void);
extern void func_02035444(int memberIndex, int flags, int memberKind, int level);
extern void func_02035d3c(void);
extern int func_ov029_020b2ee0(int proc, int group);
extern Ov022ActorEntry *func_01fffde0(int index);
extern Ov022RuntimeContext *OS_IsThreadAvailable_0x020c9848(void);

void func_ov022_0208876c(void)
{
    Ov022RootOrEntry *object;
    Ov022LimitConfig *configA;
    Ov022LimitConfig *configB;
    Ov022RuntimeContext *runtime;
    u16 limit;

    object = (Ov022RootOrEntry *)data_ov022_020b2e78.root04;
    func_02035444(1, 0, 5, func_ov002_0206e6e8());
    func_02035d3c();

    data_ov022_020b2e78.descriptor08.duplicateType04 = 1;
    data_ov022_020b2e78.descriptor08.type00 = 1;
    data_ov022_020b2e78.descriptor08.value08 = 1;
    data_ov022_020b2e78.descriptor08.sessionActive0c = 0;
    data_ov022_020b2e78.descriptor08.inputValue10 = 0;
    object->root.active1a = 1;
    object->root.group18 = 5;
    data_ov022_020b2e78.callback00 = 0;

    configA = &data_0204c77c;
    configB = &data_0204c784;
    object->root.overlayId14 = func_ov029_020b2ee0(1, 5);
    object->root.instance10 = data_ov022_020b2e78.callback00(
        &data_ov022_020b2e80);
    object = (Ov022RootOrEntry *)func_01fffde0(1);
    runtime = OS_IsThreadAvailable_0x020c9848();
    if (runtime != 0) {
        object->entry.activeObject4ec = runtime->activeObject30;
    } else {
        object->entry.activeObject4ec = 0;
    }

    limit = configB->limit06;
    if (configA->limit06 <= limit) {
        limit = configA->limit06;
    }
    object->entry.selectedLimit12 = limit;
}
