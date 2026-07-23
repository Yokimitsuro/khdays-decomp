typedef struct {
    int color;
    unsigned int flags;
} DrawTextStyle;

extern void func_020301c8(
    int context,
    int x,
    int y,
    int color,
    unsigned int flags,
    int textHandle);

void func_ov000_02059968(
    int context,
    int textHandle,
    int x,
    int y,
    DrawTextStyle style)
{
    func_020301c8(
        context,
        x + 1,
        y + 1,
        style.color - 1,
        style.flags,
        textHandle);
    func_020301c8(
        context,
        x,
        y,
        style.color,
        style.flags,
        textHandle);
}
