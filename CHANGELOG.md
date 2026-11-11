# Changelog

Notable changes to this repo. The format follows [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and versions follow [Semantic Versioning](https://semver.org); how to release:
[docs/kit/build.md](docs/kit/build.md#versioning).

## [Unreleased]

## [0.3.0] - 2026-11-12

### Added

- Provide the `nom.core` module and `nom::core` CMake target, re-exporting core types, URL
  utilities, assembly, logging and JSON configuration with transitive build dependencies.
- Export JSON mappings for `log_level`, `logfile_config` and `log_config` through the
  `nom.core:log_config` partition, preserving lowercase output and uppercase level aliases.
- Install the facade as the `nom_core` CMake package and verify consumer imports, nested
  logging configuration, serialization, defaults and invalid enum values.

## [0.2.0] - 2026-11-11

### Changed

- License project-owned code and documentation under MIT, retaining
  Alexey Tkachenko's copyright. Third-party dependencies retain their own licenses.
- Synchronize cmake_template v0.14.0 and record the repository license policy;
  the shared kit retains MIT independently of the project selection.
- Include the project license in installed artifacts alongside the applicable
  toolchain and dependency notices.
- Update internal dependency pins to `base v0.5.0`, `assembly v0.6.0`, `json_config v0.7.0`, `spd_logger v0.9.0`.

### Added

- Initialize `nom_core` from `cmake_template v0.13.0` with the `src/` source layout.
- Pin `base v0.5.0`, `assembly v0.6.0`, `spd_logger v0.9.0` and `json_config v0.7.0`,
  declaring direct dependencies before population to select one shared `base` instance.
- Add a dependency integration test and documentation for the initial repository scope.
