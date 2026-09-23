/* Draw hook of the ov218 actor's shadow model: it copies its owner's +0x384 model transform, sinks 2.0
 * lower, is scaled to 1.3 and drawn (0203bc78). */
typedef struct { int w[11]; } SrtTransform;

extern void func_0203ca9c(void *srt, int scale);
extern int func_0203bc78(char *model, int arg);

void func_ov218_020cf144(char *model, int arg)
{
    *(SrtTransform *)(model + 0x30) = *(SrtTransform *)(*(int *)(**(int **)(model + 0x84) + 0x384) + 0x30);
    *(int *)(model + 0x44) -= 0x2000;
    func_0203ca9c(model + 0x30, 0x14cd);
    func_0203bc78(model, arg);
}
