/* ov005 class descriptor data_ov005_0205b4f0, 0x0205b4f0-0x0205b504 (.data).
 *
 * InstantiateClass (02023930 / 02023960) builds a task object from it: the
 * u16 class / group ids, the constructor whose return is the first state
 * function, the method slot, the size of the zero-filled auxiliary block and
 * the arena reference.  Constructor 02053b80, method 02053c58, 0x62198-byte state.
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

extern void func_ov005_02053b80(void);
extern void func_ov005_02053c58(void);

GameClassDescriptor data_ov005_0205b4f0 = {
    8,  /* nClassId */
    14,  /* nGroupId */
    func_ov005_02053b80,  /* pfnCtor */
    func_ov005_02053c58,  /* pfnMethod */
    401816,  /* nAuxSize */
    0,  /* pArena */
};
