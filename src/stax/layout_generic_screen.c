#include <os.h>
#include "glyphs.h"

#if defined(TARGET_STAX)

#include <nbgl_obj.h>

#define UPPER_MARGIN    4
#define BUTTON_DIAMETER 80
#define ICON_X          0
#define ICON_Y          148

nbgl_image_t *generic_screen_set_icon(const nbgl_icon_details_t *icon) {
    nbgl_image_t *image = (nbgl_image_t *) nbgl_objPoolGet(IMAGE, 0);
    image->foregroundColor = BLACK;
    image->buffer = icon;
    image->obj.area.bpp = NBGL_BPP_1;
    image->obj.alignmentMarginX = ICON_X;
    image->obj.alignmentMarginY = ICON_Y;
    image->obj.alignment = TOP_MIDDLE;
    image->obj.alignTo = NULL;
    return image;
}

nbgl_text_area_t *generic_screen_set_title(nbgl_obj_t *align_to) {
    nbgl_text_area_t *textArea = (nbgl_text_area_t *) nbgl_objPoolGet(TEXT_AREA, 0);
    textArea->textColor = BLACK;
    textArea->text = "";
    textArea->textAlignment = CENTER;
    textArea->fontId = BAGL_FONT_INTER_MEDIUM_32px;
    textArea->obj.area.width = SCREEN_WIDTH - 2 * BORDER_MARGIN;
    textArea->obj.area.height = nbgl_getTextHeight(textArea->fontId, textArea->text);
    textArea->style = NO_STYLE;
    textArea->obj.alignment = BOTTOM_MIDDLE;
    textArea->obj.alignTo = align_to;
    textArea->obj.alignmentMarginX = 0;
    textArea->obj.alignmentMarginY = BORDER_MARGIN;
    return textArea;
}

void generic_screen_configure_buttons(nbgl_button_t **buttons, const size_t size) {
    nbgl_button_t *button;
    for (size_t i = 0; i < size; i++) {
        button = buttons[i];
        button->innerColor = WHITE;
        button->borderColor = LIGHT_GRAY;
        button->foregroundColor = BLACK;
        button->obj.area.width = SCREEN_WIDTH - 2 * BORDER_MARGIN;
        button->obj.area.height = BUTTON_DIAMETER;
        button->radius = BUTTON_RADIUS;
        button->fontId = BAGL_FONT_INTER_SEMIBOLD_24px;
        button->icon = NULL;
        button->obj.alignmentMarginX = 0;
        button->obj.alignmentMarginY = (button->obj.area.height + 8) * i + BORDER_MARGIN;
        button->obj.alignment = BOTTOM_MIDDLE;
        button->obj.alignTo = NULL;
        button->obj.touchMask = (1 << TOUCHED);
    }
}

nbgl_button_t *generic_screen_set_back_button() {
    nbgl_button_t *button = (nbgl_button_t *) nbgl_objPoolGet(BUTTON, 0);
    button->innerColor = WHITE;
    button->borderColor = WHITE;
    button->foregroundColor = BLACK;
    button->obj.area.width = BUTTON_DIAMETER;
    button->obj.area.height = BUTTON_DIAMETER;
    button->radius = BUTTON_RADIUS;
    button->text = NULL;
    button->icon = &C_Back_32px;
    button->obj.alignmentMarginX = 0;
    button->obj.alignmentMarginY = UPPER_MARGIN;
    button->obj.alignment = TOP_LEFT;
    button->obj.alignTo = NULL;
    button->obj.touchMask = (1 << TOUCHED);
    return button;
}

#endif
