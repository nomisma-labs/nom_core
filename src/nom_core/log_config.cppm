// SPDX-FileCopyrightText: 2026 Alexey Tkachenko
// SPDX-License-Identifier: MIT

module;

#include <json_config/config.h>

export module nom.core:log_config;

import std;
import nom.json_config;
import nom.spd_logger;

// Configuration types stay in spd_logger; their JSON mapping belongs to core integration.
export namespace nom
{
    NOM_JCONFIG_ENUM(log_level,
                     {{log_level::debug, "debug"},
                      {log_level::info, "info"},
                      {log_level::warn, "warn"},
                      {log_level::error, "error"},
                      {log_level::always, "always"},
                      {log_level::debug, "DEBUG"},
                      {log_level::info, "INFO"},
                      {log_level::warn, "WARN"},
                      {log_level::error, "ERROR"},
                      {log_level::always, "ALWAYS"}})

    NOM_JCONFIG(logfile_config, name, rotation_size)
    NOM_JCONFIG(log_config, level, file)
} // namespace nom
