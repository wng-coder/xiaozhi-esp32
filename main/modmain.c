#include "py/obj.h"
#include "py/runtime.h"
#include "application_c.h"
#include "system_info_c.h"

STATIC mp_obj_t mp_app_start(void) {
    struct Application* app = Application_GetInstance();
    Application_Start(app);
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(mp_app_start_obj, mp_app_start);

STATIC mp_obj_t mp_get_flash_size(void) {
    return mp_obj_new_int_from_ull(SystemInfo_GetFlashSize());
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(mp_get_flash_size_obj, mp_get_flash_size);

STATIC mp_obj_t mp_get_min_heap(void) {
    return mp_obj_new_int_from_ull(SystemInfo_GetMinimumFreeHeapSize());
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(mp_get_min_heap_obj, mp_get_min_heap);

STATIC mp_obj_t mp_get_free_heap(void) {
    return mp_obj_new_int_from_ull(SystemInfo_GetFreeHeapSize());
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(mp_get_free_heap_obj, mp_get_free_heap);

STATIC mp_obj_t mp_print_task_list(void) {
    SystemInfo_PrintTaskList();
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(mp_print_task_list_obj, mp_print_task_list);

STATIC mp_obj_t mp_print_heap_stats(void) {
    SystemInfo_PrintHeapStats();
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(mp_print_heap_stats_obj, mp_print_heap_stats);

STATIC const mp_rom_map_elem_t main_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_main) },
    { MP_ROM_QSTR(MP_QSTR_app_start), MP_ROM_PTR(&mp_app_start_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_flash_size), MP_ROM_PTR(&mp_get_flash_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_min_heap), MP_ROM_PTR(&mp_get_min_heap_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_free_heap), MP_ROM_PTR(&mp_get_free_heap_obj) },
    { MP_ROM_QSTR(MP_QSTR_print_task_list), MP_ROM_PTR(&mp_print_task_list_obj) },
    { MP_ROM_QSTR(MP_QSTR_print_heap_stats), MP_ROM_PTR(&mp_print_heap_stats_obj) },
};
STATIC MP_DEFINE_CONST_DICT(main_module_globals, main_module_globals_table);

const mp_obj_module_t mp_module_main = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&main_module_globals,
};

MP_REGISTER_MODULE(MP_QSTR_main, mp_module_main);
