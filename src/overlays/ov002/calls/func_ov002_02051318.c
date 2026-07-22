/* Pick the step function for the current boot mode: none while bit 2 is set,
 * otherwise bit 0 and bit 1 select one each. Reports 0 when nothing applies.
 *
 * The LAST test assigns instead of returning, which is what lets mwcc predicate
 * the whole chain into ldrne/bxne with a single shared `bx lr` -- writing it as a
 * third `return` costs a separate exit and four bytes. */
extern void func_ov002_02051354(void);
extern void func_ov002_02051438(void);

extern int data_ov002_0207f600;

void *func_ov002_02051318(void) {
    void *result = 0;
    int flags = **(int **)&data_ov002_0207f600;

    if (flags & 4) {
        return result;
    }
    if (flags & 1) {
        return (void *)&func_ov002_02051354;
    }
    if (flags & 2) {
        result = (void *)&func_ov002_02051438;
    }
    return result;
}
