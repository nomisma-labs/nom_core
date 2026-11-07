# Core integration

`nom_core` selects compatible versions of the core components and will host their shared
glue code. Its dependency setup is ready; the public glue API is still to be defined.

## Using the components

Source consumers can make `nom_core` available through CMake FetchContent and use the
existing component targets and modules directly. Declare any application-level overrides
before loading `nom_core`; the outermost FetchContent declaration selects each shared repo.
A combined `nom_core` module, library target and installed package will be defined with
its first glue components. The dependencies retain their own installed packages.

| Component | Guide |
| --- | --- |
| Common types and utilities | [base](../../external/base/README.md) |
| Component composition and event routing | [assembly](../../external/assembly/README.md) |
| Operational logging | [spd_logger](../../external/spd_logger/README.md) |
| JSON configuration | [json_config](../../external/json_config/README.md) |

## Layout

- `src/`: future shared components, registered in `src/CMakeLists.txt`.
- `external/`: pinned dependencies and their recursive dependencies.
- `tests/integration/dependencies/`: verifies JSON mapping with base types, assembly routing,
  and application logging in one consumer.
- `docs/nom_core/` and `tools/nom_core/`: repository documentation and tools as needed.

`nom_core` was initialized from `cmake_template v0.13.0`. Its exact template revision is
recorded in `.template_ref`; the template supplies build tooling through synchronized kit files.

See the [build guide](../kit/build.md), [recipes](../kit/howto.md), and
[shared documentation index](../kit/README.md).
