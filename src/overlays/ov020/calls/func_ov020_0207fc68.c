/* Creates a script task: claims a 0x15c-byte kind-0x68 record from ov002,
 * copies the caller's name into it when one is given, clears the working
 * fields and installs the three handlers.
 *
 * The name buffer is terminated before the copy so a caller that passes no
 * name still gets an empty string, which is what the state callback tests.
 */
struct Ov020ScriptTask {
    void *pOwner00;                 /* 0x00 */
    void *pNext04;
    void *pParent08;                /* 0x08, read by the state callback */
    void *p0c;
    void *p10;
    void *pOnTail14;                /* 0x14 */
    void *pOnUpdate18;              /* 0x18 */
    void *p1c;
    void *p20;
    void *p24;
    void *p28;                      /* left as the allocator wrote it */
    void *p2c;
    void *p30;
    void *p34;
    void *p38;
    void *pOnState3c;               /* 0x3c */
    void *p40;
    void *p44;
    void *p48;
    unsigned short hFlags4c;        /* 0x4c */
    char pad4e[0xa];
    char aName58[0x10];             /* 0x58 */
};

struct Ov020TaskDesc {
    char *pName;                    /* 0x00 */
};

extern struct Ov020ScriptTask *func_ov002_020769b0(int kind, int size, int arg);
extern char *strncpy(char *dst, const char *src, unsigned int n);
extern void func_ov020_0207fb04(void);
extern void func_ov020_0207fb14(void);
extern void func_ov020_0207fb8c(void);

struct Ov020ScriptTask *func_ov020_0207fc68(unsigned short id,
                                            struct Ov020TaskDesc *desc)
{
    struct Ov020ScriptTask *task;

    task = func_ov002_020769b0(0x68, 0x15c, id);
    task->aName58[0] = 0;
    if (desc->pName != 0) {
        strncpy(task->aName58, desc->pName, 0x10);
    }

    task->pOwner00 = 0;
    task->pNext04 = 0;
    task->pParent08 = 0;
    task->p0c = 0;
    task->p10 = 0;
    task->pOnTail14 = (void *)func_ov020_0207fb04;
    task->pOnUpdate18 = (void *)func_ov020_0207fb14;
    task->p1c = 0;
    task->p20 = 0;
    task->p24 = 0;
    task->p2c = 0;
    task->p30 = 0;
    task->p34 = 0;
    task->p38 = 0;
    task->p40 = 0;
    task->p44 = 0;
    task->pOnState3c = (void *)func_ov020_0207fb8c;
    task->hFlags4c = 6;
    return task;
}
