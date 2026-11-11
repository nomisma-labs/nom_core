// SPDX-FileCopyrightText: 2026 Alexey Tkachenko
// SPDX-License-Identifier: MIT

#include <json_config/config.h>
#include <spd_logger/logging.h>

#include <catch2/catch_test_macros.hpp>

import std;
import nom.core;

struct test_config
{
    nom::cfg_defaulted<nom::cfg_string> message{"default"};
    nom::cfg_defaulted<nom::log_config> log;
};
NOM_JCONFIG(test_config, message, log)

namespace
{
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

TEST_CASE("The core facade exposes its components through one import and target")
{
    const auto config = nlohmann::json{{"message", "ready"}}.get<test_config>();
    REQUIRE(*config.message == "ready");

    nom::relay<test_assembly> app;
    app.request(message_event{*config.message});
    CHECK(app.ctx().received == "ready");

    const nom::url endpoint("https://example.com:8443/market?symbol=BTC-USDT");
    CHECK(endpoint.host() == "example.com");
    CHECK(endpoint.port() == 8443);
    CHECK(endpoint.target() == "/market?symbol=BTC-USDT");

    nom::init_logger(nom::main_logger, *config.log);
    LINFO("Core dependency check: {}", app.ctx().received);
    nom::flush_logger(nom::main_logger);
}

TEST_CASE("Core logging mappings preserve defaults in nested application configs")
{
    const auto config = nlohmann::json::object().get<test_config>();
    CHECK(*config.log->level == nom::log_level::info);
    CHECK_FALSE(config.log->file.has_value());
    CHECK(config.log->validate().has_value());

    const nlohmann::json document = config;
    CHECK(document.at("log").at("level") == "info");
    CHECK(document.at("log").at("file").is_null());
}

TEST_CASE("Core logging mappings round-trip nested file settings")
{
    const auto input = nlohmann::json::parse(R"({
        "message": "ready",
        "log": {"level": "WARN", "file": {"name": "capture.log", "rotation_size": 4096}}
    })");
    const auto config = input.get<test_config>();
    CHECK(*config.log->level == nom::log_level::warn);
    REQUIRE(config.log->file.has_value());
    CHECK(config.log->file->name == "capture.log");
    REQUIRE(config.log->file->rotation_size.has_value());
    CHECK(config.log->file->rotation_size->get() == 4096);
    CHECK(config.log->validate().has_value());

    const nlohmann::json output = config;
    auto expected = input;
    expected["log"]["level"] = "warn";
    CHECK(output == expected);
    CHECK(nlohmann::json(output.get<test_config>()) == expected);
}

TEST_CASE("Core log levels accept the existing spellings and serialize in lowercase")
{
    const std::array cases{std::tuple{nom::log_level::debug, "debug", "DEBUG"},
                           std::tuple{nom::log_level::info, "info", "INFO"},
                           std::tuple{nom::log_level::warn, "warn", "WARN"},
                           std::tuple{nom::log_level::error, "error", "ERROR"},
                           std::tuple{nom::log_level::always, "always", "ALWAYS"}};
    for (const auto& [level, lower, upper] : cases)
    {
        CHECK(nlohmann::json(lower).get<nom::log_level>() == level);
        CHECK(nlohmann::json(upper).get<nom::log_level>() == level);
        CHECK(nlohmann::json(level) == lower);
    }
}

TEST_CASE("Core logging mappings reject unknown or wrongly typed levels")
{
    for (const auto& value : {nlohmann::json("verbose"), nlohmann::json("Info"), nlohmann::json(1)})
    {
        const nlohmann::json document{{"log", {{"level", value}}}};
        CHECK_THROWS_AS(document.get<test_config>(), nlohmann::json::type_error);
    }
    CHECK_THROWS_AS(nlohmann::json(static_cast<nom::log_level>(999)), nlohmann::json::type_error);
}
