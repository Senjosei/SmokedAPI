#pragma once

#include <core/types.hpp>

namespace smoked_api::app_cache {

    Vector<DLC> get_dlcs(AppId_t app_id) noexcept;

    bool save_dlcs(AppId_t app_id, const Vector<DLC>& dlcs) noexcept;

}
