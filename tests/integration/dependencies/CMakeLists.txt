# SPDX-FileCopyrightText: 2026 Alexey Tkachenko
# SPDX-License-Identifier: LicenseRef-Nomisma-Labs-Proprietary

nom_c2test(dependencies IMPORT_STD SOURCES dependencies_test.cxx
    DEPS nom::config_types nom::assembly nom::spd_logger nom::json_config
    LABELS integration)
