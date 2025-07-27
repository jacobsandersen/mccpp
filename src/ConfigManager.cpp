#include "ConfigManager.h"

namespace celerity {
const toml::value &ConfigManager::get_server_config() const {
  return m_server_config;
}
}  // namespace celerity
