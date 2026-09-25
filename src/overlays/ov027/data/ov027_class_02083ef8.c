/* ov027 class descriptor data_ov027_02083ef8, 0x02083ef8-0x02083f0c (.data).
 *
 * InstantiateClass (02023930 / 02023960) builds a task object from it: the
 * u16 class / group ids, the constructor whose return is the first state
 * function, the method slot, the size of the zero-filled auxiliary block and
 * the arena reference.  Constructor 02082bec, method 02082cd8, 0x630-byte state.
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

extern void func_ov027_02082bec(void);
extern void func_ov027_02082cd8(void);

GameClassDescriptor data_ov027_02083ef8 = {
    0,  /* nClassId */
    15,  /* nGroupId */
    func_ov027_02082bec,  /* pfnCtor */
    func_ov027_02082cd8,  /* pfnMethod */
    1584,  /* nAuxSize */
    0,  /* pArena */
};
