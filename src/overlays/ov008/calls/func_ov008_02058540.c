typedef unsigned int u32;

typedef struct Ov008LayoutTemplate {
    u32 words[4];
} Ov008LayoutTemplate;

extern Ov008LayoutTemplate data_ov008_0208e918;

extern int func_ov008_02050c54(void);
extern int func_ov008_02050f08(int tag);
extern void *func_ov008_02050f84(int index);
extern void func_ov008_02054744(int context, Ov008LayoutTemplate *layout);
extern void func_ov008_0205475c(int context, void *resource);
extern void func_ov008_02054678(int context, void *resource, int size);
extern void func_ov008_0205477c(int context, void *callback);
extern int func_ov008_02054788(int context, int id);
extern void func_ov008_02054ba4(int context, int entry, int visible);
extern void func_ov008_0205476c(int context, int id, void *callback);

extern void func_ov008_02059698(void);
extern void func_ov008_02059878(void);
extern void func_ov008_020597c4(void);
extern void func_ov008_02059898(void);
extern void func_ov008_02059934(void);
extern void func_ov008_02059960(void);
extern void func_ov008_02059980(void);
extern void func_ov008_020599a0(void);
extern void func_ov008_020599a4(void);
extern void func_ov008_02059a1c(void);
extern void func_ov008_02059a54(void);
extern void func_ov008_02059a9c(void);
extern void func_ov008_020598e4(void);
extern void func_ov008_0205990c(void);
extern void func_ov008_02059ab4(void);
extern void func_ov008_02059b14(void);
extern void func_ov008_02059b5c(void);
extern void func_ov008_02059ba4(void);
extern void func_ov008_02059bec(void);
extern void func_ov008_02059c34(void);
extern void func_ov008_02059c5c(void);

void
func_ov008_02058540(void)
{
    Ov008LayoutTemplate layout = data_ov008_0208e918;
    int context = func_ov008_02050c54();
    void *resource;

    layout.words[0] = func_ov008_02050f08(0xb);
    func_ov008_02054744(context, &layout);
    resource = func_ov008_02050f84(1);
    if (resource != 0) {
        func_ov008_0205475c(context, resource);
    }
    func_ov008_02054678(context, (void *)func_ov008_02050f08(0xc), 0x34);
    func_ov008_0205477c(context, (void *)func_ov008_02059698);

    func_ov008_02054ba4(context, func_ov008_02054788(context, 0x1f), 0);
    func_ov008_02054ba4(context, func_ov008_02054788(context, 2), 0);
    func_ov008_02054ba4(context, func_ov008_02054788(context, 1), 0);
    func_ov008_02054ba4(context, func_ov008_02054788(context, 3), 0);
    func_ov008_02054ba4(context, func_ov008_02054788(context, 4), 0);
    func_ov008_02054ba4(context, func_ov008_02054788(context, 5), 0);
    func_ov008_02054ba4(context, func_ov008_02054788(context, 6), 0);
    func_ov008_02054ba4(context, func_ov008_02054788(context, 9), 0);
    func_ov008_02054ba4(context, func_ov008_02054788(context, 0x29), 0);
    func_ov008_02054ba4(context, func_ov008_02054788(context, 0x2a), 0);
    func_ov008_02054ba4(context, func_ov008_02054788(context, 0x2b), 0);
    func_ov008_02054ba4(context, func_ov008_02054788(context, 0x2c), 0);
    func_ov008_02054ba4(context, func_ov008_02054788(context, 0x64), 1);
    func_ov008_02054ba4(context, func_ov008_02054788(context, 0x65), 1);
    func_ov008_02054ba4(context, func_ov008_02054788(context, 0x66), 1);
    func_ov008_02054ba4(context, func_ov008_02054788(context, 0x67), 1);
    func_ov008_02054ba4(context, func_ov008_02054788(context, 0x68), 1);
    func_ov008_02054ba4(context, func_ov008_02054788(context, 0x69), 1);
    func_ov008_02054ba4(context, func_ov008_02054788(context, 0x6a), 1);
    func_ov008_02054ba4(context, func_ov008_02054788(context, 0x6b), 1);

    func_ov008_0205476c(context, 1, (void *)func_ov008_02059878);
    func_ov008_0205476c(context, 2, (void *)func_ov008_020597c4);
    func_ov008_0205476c(context, 3, (void *)func_ov008_02059898);
    func_ov008_0205476c(context, 4, (void *)func_ov008_02059934);
    func_ov008_0205476c(context, 5, (void *)func_ov008_02059960);
    func_ov008_0205476c(context, 6, (void *)func_ov008_02059980);
    func_ov008_0205476c(context, 9, (void *)func_ov008_020599a0);
    func_ov008_0205476c(context, 10, (void *)func_ov008_020599a4);
    func_ov008_0205476c(context, 11, (void *)func_ov008_02059a1c);
    func_ov008_0205476c(context, 7, (void *)func_ov008_02059a54);
    func_ov008_0205476c(context, 8, (void *)func_ov008_02059a9c);
    func_ov008_0205476c(context, 12, (void *)func_ov008_020598e4);
    func_ov008_0205476c(context, 13, (void *)func_ov008_0205990c);
    func_ov008_0205476c(context, 0x65, (void *)func_ov008_02059ab4);
    func_ov008_0205476c(context, 0x66, (void *)func_ov008_02059b14);
    func_ov008_0205476c(context, 0x67, (void *)func_ov008_02059b5c);
    func_ov008_0205476c(context, 0x68, (void *)func_ov008_02059ba4);
    func_ov008_0205476c(context, 0x69, (void *)func_ov008_02059bec);
    func_ov008_0205476c(context, 0x6a, (void *)func_ov008_02059c34);
    func_ov008_0205476c(context, 0x6b, (void *)func_ov008_02059c5c);
}
