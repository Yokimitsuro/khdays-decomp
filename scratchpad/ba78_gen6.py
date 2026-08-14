import os

TYPES = """typedef struct {
    int x;
    int y;
    int z;
} Ov002Vec3;

typedef struct {
    Ov002Vec3 vecIn;
    int nField0c;
    char pad0010[0x24];
    Ov002Vec3 vecOut;
    int nValue;
} Ov002PoseEntry;

extern char *data_ov002_0207fa00;

"""

B = {}

# i1: the whole body as an inline helper taking the entry pointer
B["i1_inline_entry"] = """static inline void Ov002_ApplyPose(Ov002PoseEntry *entry, Ov002Vec3 *src, int value) {
    Ov002Vec3 *from;

    if (src == 0) {
        from = &entry->vecIn;
    } else {
        from = src;
    }
    entry->vecOut = *from;
    if (value == -1) {
        entry->nValue = entry->nField0c;
    } else {
        entry->nValue = value;
    }
}

void func_ov002_0206ba78(Ov002Vec3 *src, int value) {
    char *base = data_ov002_0207fa00 + 0x8bcc;
    int off = 0;
    int i = 0;

    do {
        Ov002_ApplyPose((Ov002PoseEntry *)(*(char **)(base + 4) + off), src, value);
        i++;
        off += 0x44;
    } while (i < 4);
}
"""

# i2: inline helper takes the table base and the byte offset
B["i2_inline_off"] = """static inline void Ov002_ApplyPose(char *base, int off, Ov002Vec3 *src, int value) {
    Ov002PoseEntry *entry = (Ov002PoseEntry *)(*(char **)(base + 4) + off);
    Ov002Vec3 *from;

    if (src == 0) {
        from = &entry->vecIn;
    } else {
        from = src;
    }
    entry->vecOut = *from;
    if (value == -1) {
        entry->nValue = entry->nField0c;
    } else {
        entry->nValue = value;
    }
}

void func_ov002_0206ba78(Ov002Vec3 *src, int value) {
    char *base = data_ov002_0207fa00 + 0x8bcc;
    int off = 0;
    int i = 0;

    do {
        Ov002_ApplyPose(base, off, src, value);
        i++;
        off += 0x44;
    } while (i < 4);
}
"""

# i3: only the copy is an inline helper
B["i3_inline_copy"] = """static inline void Ov002_CopyVec(Ov002Vec3 *dst, const Ov002Vec3 *from) {
    *dst = *from;
}

void func_ov002_0206ba78(Ov002Vec3 *src, int value) {
    char *base = data_ov002_0207fa00 + 0x8bcc;
    int off = 0;
    int i = 0;

    do {
        Ov002PoseEntry *entry = (Ov002PoseEntry *)(*(char **)(base + 4) + off);
        Ov002Vec3 *from;

        if (src == 0) {
            from = &entry->vecIn;
        } else {
            from = src;
        }
        Ov002_CopyVec(&entry->vecOut, from);
        if (value == -1) {
            entry->nValue = entry->nField0c;
        } else {
            entry->nValue = value;
        }
        i++;
        off += 0x44;
    } while (i < 4);
}
"""

# i4: the source selection is an inline helper returning the pointer
B["i4_inline_pick"] = """static inline Ov002Vec3 *Ov002_PickSource(Ov002PoseEntry *entry, Ov002Vec3 *src) {
    Ov002Vec3 *from;

    if (src == 0) {
        from = &entry->vecIn;
    } else {
        from = src;
    }
    return from;
}

void func_ov002_0206ba78(Ov002Vec3 *src, int value) {
    char *base = data_ov002_0207fa00 + 0x8bcc;
    int off = 0;
    int i = 0;

    do {
        Ov002PoseEntry *entry = (Ov002PoseEntry *)(*(char **)(base + 4) + off);

        entry->vecOut = *Ov002_PickSource(entry, src);
        if (value == -1) {
            entry->nValue = entry->nField0c;
        } else {
            entry->nValue = value;
        }
        i++;
        off += 0x44;
    } while (i < 4);
}
"""

# i5: inline helper for the copy taking the entry, so the destination member
#     expression is formed inside the callee
B["i5_inline_store"] = """static inline void Ov002_StorePose(Ov002PoseEntry *entry, const Ov002Vec3 *from) {
    entry->vecOut = *from;
}

void func_ov002_0206ba78(Ov002Vec3 *src, int value) {
    char *base = data_ov002_0207fa00 + 0x8bcc;
    int off = 0;
    int i = 0;

    do {
        Ov002PoseEntry *entry = (Ov002PoseEntry *)(*(char **)(base + 4) + off);
        Ov002Vec3 *from;

        if (src == 0) {
            from = &entry->vecIn;
        } else {
            from = src;
        }
        Ov002_StorePose(entry, from);
        if (value == -1) {
            entry->nValue = entry->nField0c;
        } else {
            entry->nValue = value;
        }
        i++;
        off += 0x44;
    } while (i < 4);
}
"""

# i6: inline helper for both the copy and the value write
B["i6_inline_tail"] = """static inline void Ov002_StorePose(Ov002PoseEntry *entry, const Ov002Vec3 *from,
                                   int value) {
    entry->vecOut = *from;
    if (value == -1) {
        entry->nValue = entry->nField0c;
    } else {
        entry->nValue = value;
    }
}

void func_ov002_0206ba78(Ov002Vec3 *src, int value) {
    char *base = data_ov002_0207fa00 + 0x8bcc;
    int off = 0;
    int i = 0;

    do {
        Ov002PoseEntry *entry = (Ov002PoseEntry *)(*(char **)(base + 4) + off);
        Ov002Vec3 *from;

        if (src == 0) {
            from = &entry->vecIn;
        } else {
            from = src;
        }
        Ov002_StorePose(entry, from, value);
        i++;
        off += 0x44;
    } while (i < 4);
}
"""

# i7: inline helper over the entry, entry declared at function scope
B["i7_inline_entry_outer"] = """static inline void Ov002_ApplyPose(Ov002PoseEntry *entry, Ov002Vec3 *src, int value) {
    Ov002Vec3 *from;

    if (src == 0) {
        from = &entry->vecIn;
    } else {
        from = src;
    }
    entry->vecOut = *from;
    if (value == -1) {
        entry->nValue = entry->nField0c;
    } else {
        entry->nValue = value;
    }
}

void func_ov002_0206ba78(Ov002Vec3 *src, int value) {
    char *base = data_ov002_0207fa00 + 0x8bcc;
    Ov002PoseEntry *entry;
    int off = 0;
    int i = 0;

    do {
        entry = (Ov002PoseEntry *)(*(char **)(base + 4) + off);
        Ov002_ApplyPose(entry, src, value);
        i++;
        off += 0x44;
    } while (i < 4);
}
"""

# i8: plain static helper, no inline keyword (should stay a call -- control probe)
B["i8_inline_vecptr"] = """static inline void Ov002_ApplyPose(Ov002PoseEntry *entry, Ov002Vec3 *src, int value) {
    Ov002Vec3 *from;
    Ov002Vec3 *dst;

    if (src == 0) {
        from = &entry->vecIn;
    } else {
        from = src;
    }
    dst = &entry->vecOut;
    *dst = *from;
    if (value == -1) {
        entry->nValue = entry->nField0c;
    } else {
        entry->nValue = value;
    }
}

void func_ov002_0206ba78(Ov002Vec3 *src, int value) {
    char *base = data_ov002_0207fa00 + 0x8bcc;
    int off = 0;
    int i = 0;

    do {
        Ov002_ApplyPose((Ov002PoseEntry *)(*(char **)(base + 4) + off), src, value);
        i++;
        off += 0x44;
    } while (i < 4);
}
"""

out = os.path.join("build", "try", "ba78")
for name, body in B.items():
    with open(os.path.join(out, name + ".c"), "w") as f:
        f.write(TYPES + body)
print("wrote %d" % len(B))
