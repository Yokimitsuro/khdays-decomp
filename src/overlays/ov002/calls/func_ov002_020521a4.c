/* Draw the entry with its resolved palette: the palette is looked up from the
 * entry's own kind byte and the caller's style byte, then passed to the renderer
 * as a fifth (stacked) argument. */
extern int func_ov002_020519b0(void *target, int kind, int style);
extern void func_ov002_02052024(void *self, signed char *entry, void *target,
                                int flags, int palette);

void func_ov002_020521a4(unsigned char *self, signed char *entry, void *target,
                         int flags) {
    int palette = func_ov002_020519b0(target, *entry, self[3]);

    func_ov002_02052024(self, entry, target, flags, palette);
}
