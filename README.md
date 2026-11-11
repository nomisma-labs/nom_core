# nom_core

<!-- repo-description:begin -->
`nom_core` integrates Nomisma's core libraries: `base`, `assembly`, `spd_logger` and
`json_config`. It selects compatible versions and provides a home for code that connects
these components.
<!-- repo-description:end -->

This initial setup pins and builds the dependencies together. Shared glue code will be
added under `src/` in subsequent work.

## Dependencies

| Repository | Pin | Purpose |
| --- | --- | --- |
| `base` | `v0.5.0` | Common types and utilities |
| `assembly` | `v0.6.0` | Component composition and event routing |
| `spd_logger` | `v0.9.0` | Operational logging |
| `json_config` | `v0.7.0` | JSON configuration mapping, loading and generation |

Dependencies are Git submodules under `external/`. CMake declares all four pins before
loading them, so `spd_logger` and `json_config` share the selected `base` instance.
Dependency applications and tests remain disabled by default when composed into this repo.

## Build

Install the tools listed in the [build guide](docs/kit/build.md#toolchain), then run:

```bash
git submodule update --init --recursive
./bootstrap.sh
```

For a single build and the dependency integration test, use
`cmake --workflow --preset complete`. The `dev` preset skips integration tests.

## Documentation

- [Core integration and component guides](docs/nom_core/README.md)
- [Build guide](docs/kit/build.md) and [development recipes](docs/kit/howto.md)
- [Changelog](CHANGELOG.md)
- [Agent instructions](AGENTS.md)

## License

This project is licensed under [MIT](LICENSE). Copyright belongs to Alexey Tkachenko.
The synchronized build kit retains its [MIT notice](cmake/kit/LICENSE); third-party
dependencies retain their own licenses.
