#!/usr/bin/env python3
"""Verify a reconstructed executable payload stored in initialized DATA.

Unlike ordinary DATA, this class may contain thousands of instructions mixed
with tables.  A receipt is issued only when the source uses ARM mnemonics for
all code, uses symbolic entries for dispatch tables, assembles to the exact
registered bytes, and survives a partial link through the project's linker.

    python tools/verify_executable_data.py <source.s> <policy-name> [--receipt]
"""

from __future__ import annotations

import hashlib
import json
import os
import re
import shutil
import subprocess
import sys
import tempfile
from datetime import datetime, timezone
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
POLICY = ROOT / "config/arm9/data_progress.json"
RECEIPTS = ROOT / "build/data_receipts"
MWLDARM = ROOT / "tools/mwccarm/2.0/sp2p4/mwldarm.exe"
LICENSE = ROOT / "tools/mwccarm/license.dat"

REFUSED = "refused"
DIFFERS = "differs"
MATCH = "match"

CODE_LABEL_RE = re.compile(r"^MobiClip_Code_([0-9A-Fa-f]{8}):$")
SYMBOLIC_WORD_RE = re.compile(
    r"^MobiClip_Code_[0-9A-Fa-f]{8}\s*-\s*\."
    r"(?:\s*\+\s*(?:0x[0-9A-Fa-f]+|[0-9]+))?$"
)
FORBIDDEN_RE = re.compile(r"^\s*\.(?:incbin|inst|insn|4byte|long|hword|short|fill|space|zero)\b", re.I)


def find_tool(name: str) -> str:
    configured = shutil.which(name)
    if configured:
        return configured
    candidates = sorted(Path("C:/Program Files (x86)").glob(
        f"Arm GNU Toolchain arm-none-eabi/*/bin/{name}.exe"
    ))
    if not candidates:
        raise FileNotFoundError(f"{name} was not found")
    return str(candidates[0])


def _integer(value) -> int:
    return int(value, 0) if isinstance(value, str) else int(value)


def load_spec(name: str, policy_path: Path = POLICY) -> dict:
    policy = json.loads(Path(policy_path).read_text(encoding="utf-8"))
    for override in policy.get("classification_overrides", []):
        if override.get("name") != name:
            continue
        verification = override.get("verification", {})
        if verification.get("format") != "arm_mnemonic_payload_v1":
            raise ValueError(f"{name} is not registered as an ARM mnemonic payload")
        spec = dict(verification)
        spec.update({
            "name": name,
            "module": override["unit"],
            "start": _integer(override["start"]),
            "end": _integer(override["end"]),
            "section": verification.get("section", "rodata"),
        })
        spec["size"] = spec["end"] - spec["start"]
        return spec
    raise KeyError(f"no DATA progress policy entry named {name}")


def _without_comment(line: str) -> str:
    return line.split("/*", 1)[0].strip()


def validate_source(text: str, spec: dict) -> dict:
    """Reject opaque encodings and prove the declared code/DATA accounting."""
    code_addresses = []
    instruction_count = 0
    data_bytes = 0
    mode = None
    awaiting_instruction = False
    saw_rodata = False

    for line_number, original in enumerate(text.splitlines(), 1):
        line = _without_comment(original)
        if not line:
            continue
        if FORBIDDEN_RE.match(line):
            raise ValueError(f"forbidden opaque directive at line {line_number}: {line}")

        code_label = CODE_LABEL_RE.match(line)
        if code_label:
            if awaiting_instruction:
                raise ValueError(f"code label without an instruction before line {line_number}")
            code_addresses.append(int(code_label.group(1), 16))
            mode = "code"
            awaiting_instruction = True
            continue

        if line.endswith(":"):
            if awaiting_instruction:
                raise ValueError(f"code label without an instruction before line {line_number}")
            mode = "data"
            continue

        if line.startswith("."):
            directive, _, operand = line.partition(" ")
            directive = directive.lower()
            operand = operand.strip()
            if awaiting_instruction:
                raise ValueError(f"directive where an ARM mnemonic is required at line {line_number}")
            if directive == ".section":
                if not operand.startswith('.rodata,"a",%progbits'):
                    raise ValueError("executable DATA source must emit an alloc-only .rodata section")
                saw_rodata = True
            elif directive == ".byte":
                if mode != "data":
                    raise ValueError(f"raw bytes outside a named DATA region at line {line_number}")
                values = [part.strip() for part in operand.split(",")]
                if not values or any(not value for value in values):
                    raise ValueError(f"empty .byte directive at line {line_number}")
                parsed = [_integer(value) for value in values]
                if any(value < 0 or value > 0xFF for value in parsed):
                    raise ValueError(f"non-byte value at line {line_number}")
                data_bytes += len(parsed)
            elif directive == ".word":
                if mode != "data":
                    raise ValueError(f"raw word outside a named DATA region at line {line_number}")
                if operand != "0" and not SYMBOLIC_WORD_RE.fullmatch(operand):
                    raise ValueError(
                        f"non-symbolic/non-reserved .word at line {line_number}: {operand}"
                    )
                data_bytes += 4
            elif directive not in {
                ".syntax", ".arch", ".arm", ".align", ".global", ".type", ".size"
            }:
                raise ValueError(f"unsupported directive at line {line_number}: {directive}")
            continue

        if not awaiting_instruction or mode != "code":
            raise ValueError(f"unexpected source text at line {line_number}: {line}")
        instruction_count += 1
        awaiting_instruction = False

    if awaiting_instruction:
        raise ValueError("final code label has no ARM mnemonic")
    if not saw_rodata:
        raise ValueError("source does not declare .rodata")
    if len(code_addresses) != len(set(code_addresses)):
        raise ValueError("duplicate ARM instruction labels")
    if code_addresses != sorted(code_addresses):
        raise ValueError("ARM instruction labels are not in address order")
    if any(address < spec["start"] or address + 4 > spec["end"] or address % 4
           for address in code_addresses):
        raise ValueError("ARM instruction label outside/alignment mismatch")
    if instruction_count != _integer(spec["instruction_count"]):
        raise ValueError(
            f"instruction count {instruction_count} != {spec['instruction_count']}"
        )
    if data_bytes != _integer(spec["embedded_data_bytes"]):
        raise ValueError(f"embedded DATA bytes {data_bytes} != {spec['embedded_data_bytes']}")
    if instruction_count * 4 + data_bytes != spec["size"]:
        raise ValueError("code plus embedded DATA does not cover the payload exactly")
    return {"instruction_count": instruction_count, "embedded_data_bytes": data_bytes}


def extract_symbol(object_path: Path, symbol_name: str, section_name: str) -> bytes:
    from elftools.elf.elffile import ELFFile

    with object_path.open("rb") as stream:
        elf = ELFFile(stream)
        symtab = elf.get_section_by_name(".symtab")
        if symtab is None:
            raise ValueError("assembled object has no symbol table")
        for symbol in symtab.iter_symbols():
            if symbol.name != symbol_name:
                continue
            section = elf.get_section(symbol["st_shndx"])
            if section.name != "." + section_name:
                raise ValueError(f"payload landed in {section.name}, expected .{section_name}")
            start = int(symbol["st_value"])
            end = start + int(symbol["st_size"])
            if len(section.data()) != int(symbol["st_size"]):
                raise ValueError("payload symbol does not own the entire output section")
            return section.data()[start:end]
    raise ValueError(f"assembled object does not define {symbol_name}")


def assemble_and_link(source: Path, spec: dict) -> tuple[bytes, bytes]:
    with tempfile.TemporaryDirectory() as directory:
        directory = Path(directory)
        assembled = directory / "payload.o"
        linked = directory / "payload_mwld.o"
        subprocess.run([
            find_tool("arm-none-eabi-as"), "-mcpu=arm946e-s",
            "-o", str(assembled), str(source),
        ], check=True, capture_output=True)
        first = extract_symbol(assembled, spec["source_symbol"], spec["section"])
        if not MWLDARM.is_file():
            raise FileNotFoundError(f"project linker was not found: {MWLDARM}")
        env = dict(os.environ, LM_LICENSE_FILE=str(LICENSE))
        subprocess.run([
            str(MWLDARM), "-proc", "arm946e", "-nostdlib", "-nodead",
            "-partial", "-main", "", "-o", str(linked), str(assembled),
        ], check=True, capture_output=True, env=env)
        second = extract_symbol(linked, spec["source_symbol"], spec["section"])
        return first, second


def verify(source, name: str, policy_path: Path = POLICY):
    try:
        spec = load_spec(name, policy_path)
        source = Path(source)
        accounting = validate_source(source.read_text(encoding="ascii"), spec)
        assembled, linked = assemble_and_link(source, spec)
    except (KeyError, ValueError, FileNotFoundError, UnicodeError) as exc:
        return REFUSED, str(exc), {}
    except subprocess.CalledProcessError as exc:
        output = (exc.stderr or exc.stdout or b"").decode(errors="replace").strip()
        return DIFFERS, f"assembler/linker failed: {output}", {}

    if len(assembled) != spec["size"]:
        return DIFFERS, f"size {len(assembled)} != {spec['size']}", {}
    digest = hashlib.sha256(assembled).hexdigest()
    if digest != spec["sha256"]:
        return DIFFERS, f"sha256 {digest} != {spec['sha256']}", {}
    if linked != assembled:
        return DIFFERS, "project linker changed the assembled payload bytes", {}
    info = {
        "kind": "executable_payload",
        "name": name,
        "symbol": spec["source_symbol"],
        "module": spec["module"],
        "section": spec["section"],
        "start": spec["start"],
        "end": spec["end"],
        "size": spec["size"],
        "sha256": digest,
        **accounting,
    }
    return MATCH, (
        f"{name} {spec['size']} bytes, {accounting['instruction_count']} ARM instructions, "
        f"{accounting['embedded_data_bytes']} embedded DATA bytes, GAS+MWLD exact"
    ), info


def _repo_path(path: Path) -> str:
    try:
        return path.resolve().relative_to(ROOT).as_posix()
    except ValueError:
        return path.resolve().as_posix()


def main() -> None:
    args = [arg for arg in sys.argv[1:] if not arg.startswith("--")]
    if len(args) != 2:
        raise SystemExit(__doc__)
    source = Path(args[0])
    name = args[1]
    status, message, info = verify(source, name)
    if status == REFUSED:
        print(">>> REFUSED <<< " + message)
        raise SystemExit(2)
    if status == DIFFERS:
        print(">>> DIFIERE <<< " + message)
        raise SystemExit(1)
    print(">>> MATCH <<< " + message)
    if "--receipt" in sys.argv:
        RECEIPTS.mkdir(parents=True, exist_ok=True)
        receipt = dict(info)
        receipt.update({
            "schema_version": 1,
            "source": _repo_path(source),
            "source_sha256": hashlib.sha256(source.read_bytes()).hexdigest(),
            "verified_at": datetime.now(timezone.utc).astimezone().isoformat(timespec="seconds"),
        })
        path = RECEIPTS / f"executable_{name}.json"
        path.write_text(json.dumps(receipt, indent=2) + "\n", encoding="utf-8", newline="\n")
        print("receipt: " + path.relative_to(ROOT).as_posix())


if __name__ == "__main__":
    main()
