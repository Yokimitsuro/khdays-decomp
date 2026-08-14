"""Semantic receipt for func_ov002_0206dc10."""
import subprocess
import sys

MARKS = [
    ("ghidra_inspected", "true"),
    ("semantic_name", "Ov002_ModuleHasKey"),
    ("function_rename_readback", "true"),
    ("function_rename_evidence",
     "Antes FUN_arm9_ov002__0206dc10. Responde si el modulo activo conoce una "
     "clave. El bit 1 del byte global en 0x0204c240 la deshabilita de raiz; si "
     "no, el id de modulo es el byte con signo en +0x8d82 del contexto raiz, se "
     "resuelve a un slot con Ov002_GetModuleSlot y la clave se busca en ese "
     "slot con ov002_LookupValueByKey; un resultado no negativo responde 1. La "
     "llama el rebuild func_ov002_0205bff4 sobre el byte bajo del nTag de una "
     "entrada, dentro del bloque que recorre la lista secundaria."),
    ("parameters_reviewed", "true"),
    ("parameters_evidence",
     "Aridad UNO, confirmada en el desensamblado: solo r0 se lee antes de "
     "escribirse, y se guarda en r4 para sobrevivir a la primera llamada. "
     "Renombrado a nKey. Read-back PARAMS 1 en r0."),
    ("locals_reviewed", "true"),
    ("locals_evidence",
     "No hay locales en pila: el marco es solo push {r4,lr} sin sub sp. La "
     "clave vive en r4, el puntero al contexto en r3 y el slot en r0. "
     "Read-back LOCALS 0, asi que no hay nada que renombrar."),
    ("prototype_readback", "true"),
    ("prototype_evidence",
     "int Ov002_ModuleHasKey(int nKey). Devuelve 0 o 1: las dos salidas "
     "tempranas hacen mov r0,#0 predicado y la final movge r0,#1 / movlt r0,#0 "
     "sobre el resultado de la busqueda, es decir una comparacion CON SIGNO "
     "contra cero. El caller usa el resultado como entero."),
    ("layout_decision", "extended"),
    ("layout_evidence",
     "Extiende el tipo existente Ov002RootContext, que ya estaba aplicado al "
     "pool slot arm9_ov002.bss::0207fa00 y mide 36254 bytes. El byte en +0x8d82 "
     "estaba SIN DEFINIR; anadido como cModuleId schar, porque el ROM lo lee "
     "con ldrsb, es decir con signo. NO entra en conflicto con el vecino "
     "pOffsetTable Ov002OffsetTable * en +0x8d7c: la funcion llega al byte por "
     "ADD, no dereferenciando ese puntero, asi que son campos distintos y "
     "pOffsetTable queda intacto. Read-back: el contexto sigue en 36254 bytes "
     "con los dos campos coexistiendo. La aritmetica del ROM registra ademas la "
     "jerarquia de la fuente original: construye el puntero como base + 0x17c, "
     "luego + 0x8c00, y deja el + 6 en el desplazamiento de la carga; eso son "
     "TRES fronteras de miembro, no un reparto arbitrario de 0x8d82, porque un "
     "campo plano en ese offset compila a base + 0x8d00 con 0x82 en el "
     "desplazamiento, que es justo lo que emitia mi primer candidato. Esa "
     "jerarquia queda registrada en el comentario del campo; no se reestructura "
     "un tipo de 36 KB por la evidencia de una sola funcion."),
    ("types_applied_readback", "true"),
    ("types_evidence",
     "Read-back por direccion: el parametro nKey int en r0, el campo cModuleId "
     "schar en +0x8d82 de Ov002RootContext junto a pOffsetTable en +0x8d7c con "
     "el tipo todavia en 36254 bytes, el pool slot arm9_ov002.bss::0207fa00 "
     "tipado Ov002RootContext *, y los prototipos de los dos callees, "
     "Ov002_GetModuleSlot y ov002_LookupValueByKey. El read-back final se hizo "
     "con un script de SOLO LECTURA."),
    ("transactions_closed", "true"),
    ("transactions_evidence",
     "Los cuatro scripts terminaron con SCRIPT COMPLETED SUCCESSFULLY sin dejar "
     "transaccion propia abierta ni errores de endTransaction, incluido el "
     "replaceAtOffset sobre el byte del contexto."),
    ("program_saved_readback", "true"),
    ("save_evidence",
     "save_program en llamada separada devolvio Program saved successfully y el "
     "read-back de solo lectura posterior informa CHANGED False."),
    ("audit_unnamed_no_new_debt", "true"),
    ("audit_unnamed_evidence",
     "tools/audit_unnamed.py: la funcion sale de la cuenta de ov002 al recibir "
     "nombre semantico, asi que la deuda baja y no se introduce ninguna nueva."),
    ("audit_struct_sync_no_new_debt", "true"),
    ("audit_struct_sync_evidence",
     "tools/audit_struct_sync.py sale con codigo 0 y no lista Ov002RootContext "
     "con variantes en conflicto. Se anadio un campo a un byte que estaba sin "
     "definir dentro del tipo existente, sin desplazar ni sombrear ningun campo "
     "ya presente, y sin crear ningun tipo rival: los tres structs anidados del "
     ".c son herramienta de codegen para mwcc, no el modelo semantico."),
]

fail = 0
for field, value in MARKS:
    r = subprocess.run([sys.executable, ".claude/hooks/khdays_control.py",
                        "semantic-mark", field, value],
                       capture_output=True, text=True)
    if r.returncode != 0:
        fail += 1
        print("%-30s FAIL %s" % (field, (r.stdout + r.stderr).strip()[:120]))
print("failures:", fail)
