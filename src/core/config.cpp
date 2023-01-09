#include <core/config.hpp>
#include <core/paths.hpp>
#include <koalabox/util.hpp>
#include <koalabox/io.hpp>

namespace config {
    Config instance; // NOLINT(cert-err58-cpp)

    // TODO: Reloading via export
    void init() {
        const auto path = paths::get_config_path();

        if (exists(path)) {
            try {
                instance = Json::parse(koalabox::io::read_file(path)).get<Config>();
            } catch (const Exception& e) {
                koalabox::util::panic("Error parsing config: {}", e.what());
            }
        }
    }

    AppStatus get_app_status(AppId_t app_id) {
        if (app_id == 0) {
            // 0 is a special internal value reserved for cases where we don't know id.
            // This is typically the case in non-koalageddon modes, hence we treat it as unlocked.
            return AppStatus::UNLOCKED;
        }

        const auto app_id_key = std::to_string(app_id);

        if (instance.override_app_status.contains(app_id_key)) {
            return instance.override_app_status[app_id_key];
        }

        return instance.default_app_status;
    }

    DlcStatus get_dlc_status(AppId_t dlc_id) {
        const auto dlc_id_key = std::to_string(dlc_id);

        if (instance.override_dlc_status.contains(dlc_id_key)) {
            return instance.override_dlc_status[dlc_id_key];
        }

        return instance.default_dlc_status;
    }

    bool is_dlc_unlocked(AppId_t app_id, AppId_t dlc_id, const Function<bool()>& original_function) {
        const auto app_status = config::get_app_status(app_id);
        const auto dlc_status = config::get_dlc_status(dlc_id);

        const auto app_unlocked = app_status == config::AppStatus::UNLOCKED;
        const auto dlc_unlocked = dlc_status == config::DlcStatus::UNLOCKED ||
                                  dlc_status != config::DlcStatus::LOCKED &&
                                  original_function();

        return app_unlocked && dlc_unlocked;
    }

    Vector<DLC> get_extra_dlcs(AppId_t app_id) {
        return DLC::get_dlcs_from_apps(instance.extra_dlcs, app_id);
    }
}
