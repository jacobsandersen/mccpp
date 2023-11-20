#include "ConfigManager.h"

const toml::value &ConfigManager::get_server_config() const {
    return m_server_config;
}
