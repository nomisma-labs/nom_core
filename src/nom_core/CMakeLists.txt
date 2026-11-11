# SPDX-FileCopyrightText: 2026 Alexey Tkachenko
# SPDX-License-Identifier: MIT

nom_lib(core IMPORT_STD STATIC
    MODULES core.cppm log_config.cppm
    PUBLIC_DEPS nom::config_types nom::base_url nom::base_enum nom::base_force_inline
        nom::assembly nom::spd_logger nom::json_config)
set_target_properties(core PROPERTIES POSITION_INDEPENDENT_CODE ON)

nom_install_package(TARGETS core DEPENDENCIES base assembly spd_logger json_config)
