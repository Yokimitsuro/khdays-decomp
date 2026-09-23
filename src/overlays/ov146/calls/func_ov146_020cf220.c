/* Spawn the ov146 actor's helper node (0203c5c0: 0x64/0xc, tick 020cf290, class 020cf320): it remembers
 * the actor and its +0x388 and +0x384 models, and the actor keeps it in +0x214. */
struct Ov146Helper { char *owner; int part; int model; };

extern int func_0203c5c0(int scene, int kind, int size, void *cb, void *cls, struct Ov146Helper **out);
extern void func_ov146_020cf290(void);
extern void func_ov146_020cf320(void);

void func_ov146_020cf220(char *self)
{
    struct Ov146Helper *helper;

    func_0203c5c0(*(int *)(self + 0x3c), 0x64, 0xc, func_ov146_020cf290, func_ov146_020cf320, &helper);
    helper->owner = self;
    helper->part = *(int *)(helper->owner + 0x388);
    helper->model = *(int *)(helper->owner + 0x384);
    *(struct Ov146Helper **)(self + 0x214) = helper;
}
