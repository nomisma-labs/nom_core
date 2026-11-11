# Core integration

`nom_core` selects compatible versions of `base`, `assembly`, `spd_logger` and `json_config`.
Its `nom.core` module provides one import for their public C++ APIs and integration code.
The underlying libraries remain independently usable and do not depend on the facade.

## Using the facade

Make `nom_core` available through CMake FetchContent, then link `nom::core`:

```cmake
nom_app(example IMPORT_STD SOURCES main.cpp DEPS nom::core)
```

Use the usual Nomisma toolchain setup for `import std` before `project()`; see the
[build guide](../kit/build.md#modules). For an installed copy, use
`find_package(nom_core CONFIG REQUIRED)` before declaring the consumer target.
The installed package finds its component packages and provides module sources for the
consumer's compiler to build.

Include macro headers directly from their owning libraries, before imports:

```cpp
#include <json_config/config.h>
#include <spd_logger/logging.h>

import std;
import nom.core;
```

`nom::core` propagates the component libraries, include directories and compile settings.
It also exposes the header-only `nom::base_enum` and `nom::base_force_inline` dependencies,
so their headers can be included directly when needed. There is no umbrella macro header.

| Repository | Re-exported modules | Guide |
| --- | --- | --- |
| `base` | `nom.config_types`, `nom.url` | [Common types and utilities](../../external/base/README.md) |
| `assembly` | `nom.assembly` | [Component composition and event routing](../../external/assembly/README.md) |
| `spd_logger` | `nom.spd_logger` | [Operational logging](../../external/spd_logger/README.md) |
| `json_config` | `nom.json_config` | [JSON configuration](../../external/json_config/README.md) |

A consumer can still link and import individual components when it needs a narrower set
of dependencies. Re-exports preserve the original types, names and module ownership.

## Logging configuration

`spd_logger` owns `nom::log_level`, `nom::logfile_config` and `nom::log_config`.
The `nom.core:log_config` interface partition supplies their exported JSON mapping functions.
Importing `nom.core` makes these mappings available to JSON conversion and application
configuration mappings:

```cpp
namespace app
{
    struct config
    {
        nom::cfg_defaulted<nom::log_config> log;
    };
    NOM_JCONFIG(config, log)
}
```

For example:

```json
{
  "log": {
    "level": "info",
    "file": {"name": "capture.log", "rotation_size": 10485760}
  }
}
```

Supported levels are `debug`, `info`, `warn`, `error` and `always`; their uppercase aliases
are also accepted. Serialization uses lowercase. Unknown names and numeric levels are rejected.
The configuration retains the logger's defaults: level `info`, console logging when `file`
is absent or null, and no rotation when `rotation_size` is absent or null.
Validation remains defined by the configuration types in `spd_logger`.

When migrating a consumer, remove its local mappings for these three types; `nom.core`
provides them. Application-specific types still use their own `NOM_JCONFIG` declarations.

## Dependency selection

Declare any intentional application-level overrides before loading `nom_core`.
CMake FetchContent uses the first declaration for each dependency; it does not check whether
an override is compatible with the rest of the selected components. `nom_core` declares all
four pins before populating them, so shared dependencies use one selected instance.
Keep the same selection when adding services that also depend on core components.

## Layout and verification

- `src/nom_core/core.cppm`: public facade and module re-exports.
- `src/nom_core/log_config.cppm`: logging configuration integration partition.
- `external/`: pinned component repositories and their dependencies.
- `tests/integration/dependencies/`: a consumer linked only to `nom::core` and importing only
  `nom.core` alongside `std`; exercises configuration, URL utilities, assembly routing and
  logging, including nested logging configuration round-trips and invalid levels.
- `docs/nom_core/` and `tools/nom_core/`: repository documentation and tools.

Run `cmake --workflow --preset ci` for the build and integration suite; the `dev` preset
excludes integration tests. The exact template revision is recorded in `.template_ref`.
See the [build guide](../kit/build.md), [recipes](../kit/howto.md), and
[shared documentation index](../kit/README.md).
