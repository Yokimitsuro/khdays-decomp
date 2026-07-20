typedef unsigned char u8;
typedef int (*OverlayCallback)(void);

typedef struct {
    int fade_counter;
    u8 pad_0004[8];
    u8 update_object[0x5068];
    void *resource;
} OverlayContext;

extern OverlayContext *NNSi_FndGetCurrentRootHeap(void);
extern OverlayContext *data_ov000_0205ac20;
extern u8 data_ov000_0205ab94[];
extern void func_0202aa9c(void *object);
extern void func_0201e374(int value);
extern void func_0201e3cc(int value);
extern void func_ov000_0204dbb4(void);
extern void *func_02023930(const void *descriptor, int argument);
extern int func_ov000_0204f324(void);

OverlayCallback func_ov000_0204f36c(void) {
    OverlayContext *context = NNSi_FndGetCurrentRootHeap();

    func_0202aa9c(context->update_object);
    if (context->fade_counter <= 16) {
        func_0201e374(-context->fade_counter);
        func_0201e3cc(-context->fade_counter);
    } else {
        func_ov000_0204dbb4();
        data_ov000_0205ac20 = context;
        func_0201e374(-16);
        func_0201e3cc(-16);
        context->resource = func_02023930(data_ov000_0205ab94, 0);
        context->fade_counter = 0;
        return func_ov000_0204f324;
    }

    context->fade_counter++;
    return 0;
}
