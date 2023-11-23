#include <glog/logging.h>
#include "BasicTimer.h"

void BasicTimer::start(const std::chrono::seconds &duration, std::function<void()> callback) {
    m_callback = std::move(callback);
    m_timer.expires_after(duration);
    m_timer.async_wait([this](const std::error_code& error) {
        if (!error) {
            LOG(INFO) << "Timer expired! Calling callback function.";
            m_callback();
        } else {
            LOG(WARNING) << "Timer: " << error.message();
        }
    });
}

void BasicTimer::cancel() {
    m_timer.cancel();
}
