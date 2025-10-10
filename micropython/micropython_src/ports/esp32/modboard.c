#include "py/runtime.h"
#include "components/board_wrapper/board_wrapper.h"

// MicroPython wrapper for Board class

typedef struct _mp_obj_board_t {
    mp_obj_base_t base;
    void* board;
} mp_obj_board_t;

static mp_obj_t board_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args) {
    mp_obj_board_t *self = m_new_obj(mp_obj_board_t);
    self->base.type = type;
    self->board = board_wrapper_create();
    return MP_OBJ_FROM_PTR(self);
}

static mp_obj_t board_get_type(mp_obj_t self_in) {
    mp_obj_board_t *self = MP_OBJ_TO_PTR(self_in);
    const char* type = board_wrapper_get_type(self->board);
    return mp_obj_new_str(type, strlen(type));
}
static MP_DEFINE_CONST_FUN_OBJ_1(board_get_type_obj, board_get_type);

static mp_obj_t board_get_uuid(mp_obj_t self_in) {
    mp_obj_board_t *self = MP_OBJ_TO_PTR(self_in);
    const char* uuid = board_wrapper_get_uuid(self->board);
    return mp_obj_new_str(uuid, strlen(uuid));
}
static MP_DEFINE_CONST_FUN_OBJ_1(board_get_uuid_obj, board_get_uuid);

// Add more wrappers for LED, Backlight, AudioCodec, Network, etc. as needed

static const mp_rom_map_elem_t board_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_get_type), MP_ROM_PTR(&board_get_type_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_uuid), MP_ROM_PTR(&board_get_uuid_obj) },
    // Add more methods here
};
static MP_DEFINE_CONST_DICT(board_locals_dict, board_locals_dict_table);

MP_DEFINE_CONST_OBJ_TYPE(
    board_type,
    MP_QSTR_Board,
    MP_TYPE_FLAG_NONE,
    make_new, board_make_new,
    locals_dict, &board_locals_dict
);

static const mp_rom_map_elem_t board_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR_Board), MP_ROM_PTR(&board_type) },
};
static MP_DEFINE_CONST_DICT(board_module_globals, board_module_globals_table);

const mp_obj_module_t board_user_cmodule = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&board_module_globals,
};

MP_REGISTER_MODULE(MP_QSTR_board, board_user_cmodule);
