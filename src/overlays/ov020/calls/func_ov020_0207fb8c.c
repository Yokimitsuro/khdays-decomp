/* State-change callback for a script task's scene node: entering state 0 hides
 * the node, entering state 1 shows it, and state 2 is accepted and ignored.
 *
 * Both arms first check the sprite's visibility byte, and the sprite pointer is
 * loaded before the dispatch rather than inside the arms, so the load sits
 * above the switch.
 */
struct Ov020Sprite {
    char pad00[0x58];
    signed char bVisible58;                 /* 0x58 */
};

struct Ov020ScriptTask {
    char pad00[8];
    struct Ov020Sprite *pSprite08;          /* 0x08 */
    char pad0c[0x10];
    unsigned short aSceneNode1c[1];         /* 0x1c */
};

extern void func_0202af1c(unsigned short *node);
extern void func_0202af2c(unsigned short *node);

void func_ov020_0207fb8c(struct Ov020ScriptTask *task, int state)
{
    struct Ov020Sprite *sprite = task->pSprite08;

    switch (state) {
    case 0:
        if (sprite->bVisible58 != 0) {
            func_0202af2c(task->aSceneNode1c);
        }
        break;
    case 1:
        if (sprite->bVisible58 != 0) {
            func_0202af1c(task->aSceneNode1c);
        }
        break;
    case 2:
        break;
    }
}
