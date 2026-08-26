typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct Ov022SelectionPoint {
    int x;
    int y;
} Ov022SelectionPoint;

typedef struct Ov022Type1Source {
    char pad_0000[0x21a];
    u16 row21a;
} Ov022Type1Source;

typedef struct Ov022TargetEntry {
    char pad_0000[0x12];
    u16 flags12;
} Ov022TargetEntry;

typedef struct Ov022Actor {
    u64 flags0;
} Ov022Actor;

typedef struct Ov022SelectionController {
    u32 flags0;
    u32 selectionFlags4;
    int type8;
    Ov022Type1Source *type1SourceC;
    void **type1List10;
    char pad_0014[4];
    Ov022TargetEntry *targetEntry18;
    void *type3Source1c;
    char pad_0020[0x1c];
    char type13State3c[0xac];
    char subsystemE8[0x148];
    int activationState230;
} Ov022SelectionController;

extern u16 data_0204c190;

extern Ov022SelectionController *NNSi_FndGetCurrentRootHeap(void);
extern int func_01fffe14(void);
extern int func_020358f4(int index, int parameter);
extern void func_ov002_020592f8(unsigned int row, int argument);
extern void func_ov022_02086128(void *subsystem);
extern void *func_ov002_02076d24(Ov022TargetEntry *entry);
extern void func_ov022_02086098(void *subsystem, Ov022TargetEntry *entry);
extern Ov022Actor *func_01fffde0(int index);
extern void func_ov022_020852c0(int enabled);
extern int func_ov022_02085ec4(void *target, Ov022SelectionPoint *out);
extern void func_ov022_020863d0(void *state, const Ov022SelectionPoint *point);
extern void func_ov022_02086138(void *subsystem,
                                const Ov022SelectionPoint *point);

void func_ov022_02085d00(void)
{
    Ov022SelectionPoint point;
    Ov022SelectionController *context = NNSi_FndGetCurrentRootHeap();
    void *target = 0;

    if (context->type8 == 0) {
        return;
    }
    if ((context->selectionFlags4 & 2) == 0) {
        return;
    }

    switch (context->type8) {
    case 1:
        if (func_020358f4(func_01fffe14(), 0x53) != 0) {
            func_ov002_020592f8(context->type1SourceC->row21a, 7);
        }
        target = (char *)*context->type1List10 + 4;
        func_ov022_02086128(context->subsystemE8);
        break;

    case 2: {
        void *resolvedTarget =
            func_ov002_02076d24(context->targetEntry18);
        if (resolvedTarget != 0) {
            target = resolvedTarget;
            if ((context->targetEntry18->flags12 & 0x80) == 0) {
                func_ov022_02086098(context->subsystemE8,
                                    context->targetEntry18);
            }
        }
        break;
    }

    case 3:
        target = (char *)context->type3Source1c + 0xf8;
        target = (char *)target + 0x800;
        func_ov022_02086128(context->subsystemE8);
        break;
    }

    {
        Ov022Actor *actor = func_01fffde0(func_01fffe14());
        if ((data_0204c190 & 4) != 0 &&
            (actor->flags0 & 0x1000000ULL) == 0 &&
            (context->flags0 & 4) != 0) {
            func_ov022_020852c0(0);
            return;
        }
    }

    if (target == 0) {
        return;
    }
    if (func_ov022_02085ec4(target, &point) == -1) {
        return;
    }

    switch (context->type8) {
    case 1:
        func_ov022_020863d0(context->type13State3c, &point);
        return;

    case 2:
        if ((context->targetEntry18->flags12 & 0x80) != 0) {
            return;
        }
        func_ov022_02086138(context->subsystemE8, &point);
        return;

    case 3:
        func_ov022_020863d0(context->type13State3c, &point);
        return;
    }
}

