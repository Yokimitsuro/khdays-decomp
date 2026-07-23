extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov000_02056884(void *spriteContext, int sprite, int x, int y);
extern void func_ov000_020568ac(void *spriteContext, int sprite);

typedef struct {
    short firstRow;
    short selectedRow;
    char pad04[0x108];
    char spriteContext[0xd034];
    int normalRowSprite;
    int selectedRowSprite;
} Ov000MenuContext;

void func_ov000_02059d08(void)
{
    Ov000MenuContext *context = (Ov000MenuContext *)NNSi_FndGetCurrentRootHeap();
    int i;
    int selected;
    short y;

    y = 2;
    i = 0;
    selected = context->selectedRow - context->firstRow;

    for (; i < 10; i++) {
        int sprite;
        if (selected == i) {
            sprite = context->selectedRowSprite;
        } else {
            sprite = context->normalRowSprite;
        }
        func_ov000_02056884(context->spriteContext, sprite, 2, y);
        func_ov000_020568ac(context->spriteContext, sprite);
        y += 2;
    }
}
