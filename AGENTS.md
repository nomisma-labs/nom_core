# AGENTS.md

<!-- repo-description:begin -->
`nom_core` integrates the `base`, `assembly`, `spd_logger` and `json_config` repositories.
It pins their compatible releases and will hold glue code that spans their APIs. The current
setup contains dependency wiring and an integration test; shared component APIs come later.
<!-- repo-description:end -->

Read and follow the rules every Nomisma repo shares: @docs/kit/agents.md

Rules for this repo alone follow below.

- Declare all direct FetchContent pins before making any dependency available, so shared
  transitive dependencies resolve to the selected top-level versions.
- Keep reusable integration code under `src/`, documentation under `docs/nom_core/`, and
  repository-specific tools under `tools/nom_core/`.
- Keep transport and execution services in the service layer. This repository integrates
  core types, composition, configuration and logging.
- Add shared glue APIs when their contracts are requested; dependency preparation alone
  does not define an umbrella C++ module or library target.
