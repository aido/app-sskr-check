#pragma once

#if defined(SCREEN_SIZE_WALLET)

nbgl_image_t *generic_screen_set_icon(const nbgl_icon_details_t *icon);
nbgl_text_area_t *generic_screen_set_title(nbgl_obj_t *align_to);
void generic_screen_configure_buttons(nbgl_button_t **buttons, const size_t size);
nbgl_button_t *generic_screen_set_back_button();

#endif
