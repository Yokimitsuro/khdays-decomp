typedef unsigned char u8;
typedef signed short s16;

typedef struct {
    int x;
    int y;
} OverlayVector;

typedef struct {
    s16 value_0;
    s16 value_2;
    u8 pad_0004[0x4bd4];
    u8 object[0x8570];
    int *first_handle;
    int *second_handle;
    int *position_handle;
} OverlayContext;

extern OverlayContext *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov000_02055cb4(void *object, int *handle, int enabled);
extern OverlayVector *func_ov000_02055c40(void *object, int *handle);
extern void func_ov000_02055bfc(void *object, int *handle,
                                const OverlayVector *value);

void func_ov000_02059a68(void) {
    OverlayContext *context = NNSi_FndGetCurrentRootHeap();
    OverlayVector position;

    func_ov000_02055cb4(context->object, context->first_handle,
                        context->value_0 != 0);
    func_ov000_02055cb4(context->object, context->second_handle,
                        context->value_0 < 18);

    position = *func_ov000_02055c40(context->object,
                                    context->position_handle);
    position.y += (context->value_2 - context->value_0) << 16;
    func_ov000_02055bfc(context->object, context->position_handle, &position);
}
