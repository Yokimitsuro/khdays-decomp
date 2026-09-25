/* ov006 class descriptor data_ov006_0205652c, 0x0205652c-0x02056540 (.data).
 *
 * InstantiateClass (02023930 / 02023960) builds a task object from it: the
 * u16 class / group ids, the constructor whose return is the first state
 * function, the method slot, the size of the zero-filled auxiliary block and
 * the arena reference.  Constructor 0205454c, method 0205487c, 0x97f8-byte state.
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

extern void func_ov006_0205454c(void);
extern void func_ov006_0205487c(void);

GameClassDescriptor data_ov006_0205652c = {
    8,  /* nClassId */
    14,  /* nGroupId */
    func_ov006_0205454c,  /* pfnCtor */
    func_ov006_0205487c,  /* pfnMethod */
    38904,  /* nAuxSize */
    0,  /* pArena */
};
