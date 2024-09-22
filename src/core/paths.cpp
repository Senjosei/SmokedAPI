#include <core/paths.hpp>
#include <core/globals.hpp>
#include <koalabox/loader.hpp>

// TODO: Refactor to KoalaBox
namespace paths {

    Path get_self_path() {
        static const auto path = koalabox::loader::get_module_dir(globals::smokedapi_handle);
        return path;
    }

    Path get_config_path() {
        static const auto path = get_self_path() / "SmokedAPI.config.json";
        return path;
    }

    Path get_cache_path() {
        static const auto path = get_self_path() / "SmokedAPI.cache.json";
        return path;
    }

    Path get_log_path() {
        static const auto path = get_self_path() / "SmokedAPI.log.log";
        return path;
    }

}
