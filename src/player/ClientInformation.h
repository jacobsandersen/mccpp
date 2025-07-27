#ifndef MCCPP_CLIENTINFORMATION_H
#define MCCPP_CLIENTINFORMATION_H

#include <string>

namespace celerity::player {
class ClientInformation {
 public:
  [[nodiscard]] const std::string &get_locale() const;

  void set_locale(const std::string &locale);

  [[nodiscard]] int8_t get_view_distance() const;

  void set_view_distance(int8_t view_distance);

  [[nodiscard]] int32_t get_chat_mode() const;

  void set_chat_mode(int32_t chat_mode);

  [[nodiscard]] bool are_chat_colors_enabled() const;

  void set_chat_colors_enabled(bool chat_colors_enabled);

  [[nodiscard]] uint8_t get_displayed_skin_parts() const;

  void set_displayed_skin_parts(uint8_t displayed_skin_parts);

  [[nodiscard]] int32_t get_main_hand() const;

  void set_main_hand(int32_t main_hand);

  [[nodiscard]] bool is_text_filtering_enabled() const;

  void set_text_filtering_enabled(bool enable_text_filtering);

  [[nodiscard]] bool does_allow_server_listings() const;

  void set_allow_server_listings(bool allow_server_listings);

 private:
  std::string m_locale{};
  int8_t m_view_distance{};
  int32_t m_chat_mode{};
  bool m_chat_colors_enabled{};
  uint8_t m_displayed_skin_parts{};
  int32_t m_main_hand{};
  bool m_enable_text_filtering{};
  bool m_allow_server_listings{};
};
}  // namespace celerity::player

#endif  // MCCPP_CLIENTINFORMATION_H
