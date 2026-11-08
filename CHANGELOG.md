# Changelog

Notable changes to this repo. The format follows [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and versions follow [Semantic Versioning](https://semver.org); how to release:
[docs/kit/build.md](docs/kit/build.md#versioning).

## [Unreleased]

### Added

- Initialize `nom_core` from `cmake_template v0.13.0` with the `src/` source layout.
- Pin `base v0.4.0`, `assembly v0.5.0`, `spd_logger v0.8.0` and `json_config v0.6.0`,
  declaring direct dependencies before population to select one shared `base` instance.
- Add a dependency integration test and documentation for the initial repository scope.
