# AGENTS.md

<!-- repo-description:begin -->
`nom_core` integrates the `base`, `assembly`, `spd_logger` and `json_config` repositories.
It pins their compatible releases. The `nom.core` facade and `nom::core` CMake target expose
their public APIs, with logging configuration JSON mappings in `nom.core:log_config`.
<!-- repo-description:end -->

Read and follow the rules every Nomisma repo shares: @docs/kit/agents.md

Rules for this repo alone follow below.

- Declare all direct FetchContent pins before making any dependency available, so shared
  transitive dependencies resolve to the selected top-level versions.
- Keep reusable integration code under `src/`, documentation under `docs/nom_core/`, and
  repository-specific tools under `tools/nom_core/`.
- Keep transport and execution services in the service layer. This repository integrates
  core types, composition, configuration and logging.
- Keep underlying libraries independent of `nom.core`. Re-export their public modules and
  place cross-library glue in facade interface partitions.
- Clients include macro headers directly from their owning libraries; do not add an umbrella
  macro header. Test consumer code through `import nom.core` and the `nom::core` target.
