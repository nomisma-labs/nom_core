// SPDX-FileCopyrightText: 2026 Alexey Tkachenko
// SPDX-License-Identifier: LicenseRef-Nomisma-Labs-Proprietary

#include <json_config/config.h>
#include <spd_logger/logging.h>

#include <catch2/catch_test_macros.hpp>

import std;
import nom.config_types;
import nom.assembly;
import nom.json_config;
import nom.spd_logger;

namespace
{
    struct test_config
    {
        nom::cfg_defaulted<nom::cfg_string> message{"default"};
    };
    NOM_JCONFIG(test_config, message)

    struct message_event
    {
        std::string_view text;
    };

    template <typename Traits> struct receiver
    {
        struct context_mixin
        {
            std::string received;
        };

        void on_request(message_event event)
        {
            nom::ctx(this).received = event.text;
        }
    };

    struct test_assembly : nom::assembly<test_assembly, receiver>
    {
    };
} // namespace

TEST_CASE("Core dependencies work together in one consumer")
{
    const auto config = nlohmann::json{{"message", "ready"}}.get<test_config>();
    REQUIRE(*config.message == "ready");

    nom::relay<test_assembly> app;
    app.request(message_event{*config.message});
    CHECK(app.ctx().received == "ready");

    nom::init_logger(nom::main_logger);
    LINFO("Core dependency check: {}", app.ctx().received);
    nom::flush_logger(nom::main_logger);
}
