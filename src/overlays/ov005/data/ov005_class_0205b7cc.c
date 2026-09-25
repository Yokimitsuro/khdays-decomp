/* ov005 class descriptor data_ov005_0205b7cc, 0x0205b7cc-0x0205b7e0 (.data).
 *
 * InstantiateClass (02023930 / 02023960) builds a task object from it: the
 * u16 class / group ids, the constructor whose return is the first state
 * function, the method slot, the size of the zero-filled auxiliary block and
 * the arena reference.  Constructor 020586ac, method 0205873c, 0x3c-byte state.
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

extern void func_ov005_020586ac(void);
extern void func_ov005_0205873c(void);

GameClassDescriptor data_ov005_0205b7cc = {
    8,  /* nClassId */
    15,  /* nGroupId */
    func_ov005_020586ac,  /* pfnCtor */
    func_ov005_0205873c,  /* pfnMethod */
    60,  /* nAuxSize */
    0,  /* pArena */
};
