typedef unsigned char u8;

typedef struct OverlayVector {
    int x;
    int y;
} OverlayVector;

typedef struct Ov000HandleGroup {
    int *firstHandle;
    int *lastHandle;
    int *handles[16];
    int count;
    int inputValue;
    int unknown50;
    int visibleCount;
    int unknown58;
    int unknown5c;
} Ov000HandleGroup;

typedef struct Ov000ListObjectArea {
    u8 pad_0000[0x4800];
    u8 object[1];
} Ov000ListObjectArea;

typedef struct Ov000ListSceneContext {
    u8 pad_0000[8];
    Ov000HandleGroup handleGroup;
    u8 pad_0068[0x370];
    Ov000ListObjectArea objectArea;
} Ov000ListSceneContext;

extern Ov000ListSceneContext *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov000_02055bfc(void *object, int *handle,
                                const OverlayVector *position);
extern void func_ov000_02055cb4(void *object, int *handle, int enabled);

void func_ov000_02059264(int row) {
    Ov000ListSceneContext *context = NNSi_FndGetCurrentRootHeap();
    Ov000HandleGroup *group = &context->handleGroup;
    OverlayVector position;
    int i;
    Ov000ListObjectArea *objectArea = &context->objectArea;

    position.x = 0xe8000;
    position.y = (row + 0x10) << 12;
    func_ov000_02055bfc(objectArea->object, group->firstHandle, &position);

    position.y += 0x10000;
    for (i = 0; i < group->count; i++) {
        func_ov000_02055cb4(objectArea->object, group->handles[i], 1);
        func_ov000_02055bfc(objectArea->object, group->handles[i], &position);
        position.y += 0x8000;
    }

    func_ov000_02055bfc(objectArea->object, group->lastHandle, &position);
}
