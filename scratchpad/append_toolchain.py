import io

P = ".claude/skills/khdays-decomp/references/toolchain.md"
TEXT = u"""

## Regenerar PROGRESS.md y README.md antes de cada push

Los dos ficheros de estado del repositorio son GENERADOS y no se editan a mano,
igual que `delinks.txt`. Antes de cada push, despues de que el gate completo
devuelva `DSD_OK=306 FAILED=0` y antes del commit del lote:

```bash
python tools/progress.py && python tools/update_readme.py
```

`tools/progress.py` reescribe `PROGRESS.md` entero. `tools/update_readme.py`
reescribe solo las celdas de conteo de la tabla de estado de `README.md` y deja
intactas etiquetas y descripciones. Los dos comparten la misma clasificacion,
`audit_progress` mas `compute_byte_progress`, de modo que no pueden discrepar
entre si; por eso se ejecutan siempre juntos y en ese orden.

Los dos `.md` regenerados entran en el MISMO commit que las funciones del lote,
no en uno aparte: si se sube codigo sin regenerarlos, las cifras publicadas se
quedan por detras del arbol y el progreso real deja de ser auditable desde
fuera del repositorio.
"""

with io.open(P, "a", encoding="utf-8") as f:
    f.write(TEXT)
print("appended", len(TEXT))
