/* ov010 class descriptor data_ov010_0204cfa0, 0x0204cfa0-0x0204cfb4 (.data).
 *
 * InstantiateClass (02023930 / 02023960) builds a task object from it: the
 * u16 class / group ids, the constructor whose return is the first state
 * function, the method slot, the size of the zero-filled auxiliary block and
 * the arena reference.  Constructor 0204cb3c, method 0204cd80, 0x100-byte state.
 */

typedef void (*GameClassFn)(void);

typedef struct GameClassDescriptor {
    unsigned short nClassId;  /* 0x00 */
    unsigned short nGroupId;  /* 0x02 */
    GameClassFn pfnCtor;      /* 0x04: returns the object's first state fn */
    GameClassFn pfnMethod;    /* 0x08 */
    int nAuxSize;             /* 0x0c: zero-filled state block */
    int *pArena;              /* 0x10 */
} GameClassDescriptor;

extern void func_ov010_0204cb3c(void);
extern void func_ov010_0204cd80(void);
extern int data_0204c024;

GameClassDescriptor data_ov010_0204cfa0 = {
    0,  /* nClassId */
    15,  /* nGroupId */
    func_ov010_0204cb3c,  /* pfnCtor */
    func_ov010_0204cd80,  /* pfnMethod */
    256,  /* nAuxSize */
    &data_0204c024,  /* pArena */
};
