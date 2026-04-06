# BASguid — specification

## Purpose

Provide a **small API** that returns a **human-readable globally unique identifier** string suitable for logging, correlation IDs, test object names, and opaque primary keys when a full database sequence is unavailable.

“Human-readable” means: printable ASCII, visually scannable, copy/paste friendly, and **not** raw binary.

## Out of scope

- Parsing or validating GUID strings returned by other systems.
- Cryptographic guarantees beyond “random UUID-style” (see below).
- Persistence, namespaces, or OID registries.

## Recommended format (canonical)

**RFC 4122 UUID version 4** in the usual textual form:

- 36 characters: `8-4-4-4-12` lowercase **hexadecimal** digits with **hyphens** as separators.
- Example: `f47ac10b-58cc-4372-a567-0e02b2c3d479`.

Properties:

- **Charset:** `0-9`, `a-f`, `-` only.
- **Fixed length:** always 36 bytes (excluding a C string null terminator if applicable).
- **Version nibble:** bit pattern consistent with UUID v4 (random).
- **Variant:** RFC 4122 variant in the high bits of the clock_seq/reserved octet.

This is the default interpretation of “GUID” in this codebase unless a future revision explicitly defines an alternate encoding (e.g. ULID).

## API (implemented)

```cpp
#include <BAS/BASguid.h>

BASstring BASguid(int Size);
```

Semantics:

- `Size <= 0` or `Size > 4096` — returns an **empty** `BASstring`.
- `Size == 36` — RFC 4122 **UUID v4** (lowercase hex, hyphens at 8/13/18/23); entropy from `/dev/urandom` (POSIX) or `RtlGenRandom` (Windows).
- `Size == 32` — same 16 bytes as a v4 UUID, **32 hex digits** (no hyphens).
- Otherwise — exactly `Size` lowercase **hex** digits from random bytes (no UUID version/variant layout).

Random bytes are read in one shot (or via Windows API); implementation is **stateless** and safe to call concurrently.

Requirements:

- **Idempotent usage:** each call produces a **new** identifier (no hidden global “current id” unless documented otherwise).
- **Allocation:** if returning `BASstring`, document whether it allocates on the heap; if writing into a caller buffer, document required size (≥ 37 bytes for a C string including `'\0'` for the canonical form).

Optional (not required for v1):

- `BASguidMakeInto(char* pBuf, int bufSize)` with `bufSize >= 37` for fixed buffers.

## Randomness and uniqueness

- **Source:** use a platform-appropriate **non-deterministic** RNG suitable for UUID v4 (e.g. OS CSPRNG: `/dev/urandom`, `getrandom`, `BCryptGenRandom`, etc., not `rand()` alone).
- **Collision:** treat as negligible for practical purposes (same assumptions as standard UUID v4).
- **Do not** seed a PRNG from time alone for production identifiers.

## Thread safety

Document whether concurrent calls from multiple threads are safe without external locking. Prefer **stateless** implementation so calls are naturally thread-safe.

## Logging and tracing

If `CORlog` / `BAS_TRACE` is used in the implementation, follow project rules: `COR_LOG_MODULE` in `.cpp` only, narrowest level, etc.

## File layout (implementation preview)

Suggested locations (when implemented):

- `cpp/BAS/BASguid.h` — declarations.
- `cpp/BAS/BASguid.cpp` — implementation (platform RNG).

Header banner per project rules (copyright, `#pragma once`, no `// Date:` line).

## Acceptance criteria

- Generated strings match the **canonical format** (length 36, hyphen positions, lowercase hex).
- Version and variant bits satisfy **UUID v4 / RFC 4122** when decoded from hex.
- Documented randomness source meets the **non-`rand()`** requirement above.
- A short unit or smoke test builds a number of IDs and checks format (regex or fixed positions) and non-equality with high probability (e.g. sample of N ≥ 1000 with no duplicates).
