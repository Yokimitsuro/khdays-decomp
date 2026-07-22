/* Create the 0xc-byte object at data_ov002_0207f62c once, seeding it from the
 * two-word template at data_ov002_0207e358. Already-created is the common case
 * and does nothing -- but the template is copied to the stack BEFORE the check,
 * because it is an ordinary initialised local. */
typedef struct {
    int nFirst;
    int nSecond;
} Ov002SeedTemplate;

extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned int size);
extern void func_ov002_0206675c(void *obj, const Ov002SeedTemplate *seed);
extern void func_ov002_02066280(void);

extern Ov002SeedTemplate data_ov002_0207e358;
extern void *data_ov002_0207f62c;

void func_ov002_020636dc(void) {
    Ov002SeedTemplate seed = data_ov002_0207e358;

    if (data_ov002_0207f62c == 0) {
        void *obj = NNSi_FndAllocFromDefaultExpHeap(0xc);

        data_ov002_0207f62c = obj;
        func_ov002_0206675c(obj, &seed);
        func_ov002_02066280();
    }
}
