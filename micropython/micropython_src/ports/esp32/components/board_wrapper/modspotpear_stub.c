#include "py/runtime.h"

// Stub for spotpear module to satisfy linker
// This prevents the build system from looking for the full spotpear module

static mp_obj_t spotpear_stub_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args) {
    mp_raise_NotImplementedError(MP_ERROR_TEXT("SpotPear module not implemented in this build"));
}

const mp_obj_type_t spotpear_stub_type = {
    { &mp_type_type },
    .name = MP_QSTR___name__,
    .make_new = spotpear_stub_make_new,
};

static const mp_rom_map_elem_t spotpear_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_spotpear) },
};
static MP_DEFINE_CONST_DICT(spotpear_module_globals, spotpear_module_globals_table);

const mp_obj_module_t spotpear_user_cmodule = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&spotpear_module_globals,
};

MP_REGISTER_MODULE(MP_QSTR_spotpear, spotpear_user_cmodule);