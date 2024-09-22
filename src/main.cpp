#include <smoked_api/smoked_api.hpp>

// This header will be populated at build time
#include <linker_exports.h>

EXTERN_C [[maybe_unused]] BOOL WINAPI DllMain(HMODULE module_handle, DWORD reason, LPVOID) {
    if (reason == DLL_PROCESS_ATTACH) {
        smoked_api::init(module_handle);
    } else if (reason == DLL_PROCESS_DETACH) {
        smoked_api::shutdown();
    }

    return TRUE;
}
