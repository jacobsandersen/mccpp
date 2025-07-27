#ifndef MCCPP_CONFIGMANAGER_H
#define MCCPP_CONFIGMANAGER_H

#include <toml.hpp>

namespace celerity {
class ConfigManager {
 public:
  ConfigManager() : m_server_config(toml::parse("../server.toml")) {}

  [[nodiscard]] const toml::value &get_server_config() const;

 private:
  toml::value m_server_config;
};
}  // namespace celerity

#endif  // MCCPP_CONFIGMANAGER_H
