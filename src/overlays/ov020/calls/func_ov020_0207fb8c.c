/* State-change callback for a script task's scene node: entering state 0 hides
 * the node, entering state 1 shows it, and state 2 is accepted and ignored.
 *
 * Both arms first check that the parent task is named -- the test is on the
 * first byte of its sixteen-byte name, which the task constructor terminates
 * before copying anything into it. The parent pointer is loaded before the
 * dispatch rather than inside the arms, so the load sits above the switch.
 */
struct Ov020ScriptTask {
    char pad00[8];
    struct Ov020ScriptTask *pParent08;      /* 0x08 */
    char pad0c[0x10];
    unsigned short aSceneNode1c[1];         /* 0x1c */
    char pad1e[0x3a];
    char aName58[0x10];                     /* 0x58 */
};

extern void func_0202af1c(unsigned short *node);
extern void func_0202af2c(unsigned short *node);

void func_ov020_0207fb8c(struct Ov020ScriptTask *task, int state)
{
    struct Ov020ScriptTask *parent = task->pParent08;

    switch (state) {
    case 0:
        if (parent->aName58[0] != 0) {
            func_0202af2c(task->aSceneNode1c);
        }
        break;
    case 1:
        if (parent->aName58[0] != 0) {
            func_0202af1c(task->aSceneNode1c);
        }
        break;
    case 2:
        break;
    }
}
