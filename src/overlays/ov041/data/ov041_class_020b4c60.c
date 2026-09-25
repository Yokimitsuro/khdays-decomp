/* ov041 class descriptor data_ov041_020b4c60, 0x020b4c60-0x020b4c74 (.data).
 *
 * InstantiateClass (02023930 / 02023960) builds a task object from it: the
 * u16 class / group ids, the constructor whose return is the first state
 * function, the method slot, the size of the zero-filled auxiliary block and
 * the arena reference.  Constructor 020b3234, method 020b325c, 0x32ec-byte state.
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

extern void func_ov041_020b3234(void);
extern void func_ov041_020b325c(void);

GameClassDescriptor data_ov041_020b4c60 = {
    10,  /* nClassId */
    6,  /* nGroupId */
    func_ov041_020b3234,  /* pfnCtor */
    func_ov041_020b325c,  /* pfnMethod */
    13036,  /* nAuxSize */
    0,  /* pArena */
};
