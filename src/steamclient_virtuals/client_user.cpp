#include <core/macros.hpp>
#include <steam_impl/steam_apps.hpp>

VIRTUAL(bool) IClientUser_BIsSubscribedApp(PARAMS(AppId_t app_id)) {
    return steam_apps::IsDlcUnlocked(__func__, 0, app_id, [&]() {
        GET_ORIGINAL_HOOKED_FUNCTION(IClientUser_BIsSubscribedApp)

        return IClientUser_BIsSubscribedApp_o(ARGS(app_id));
    });
}
