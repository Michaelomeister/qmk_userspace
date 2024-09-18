RGB_MATRIX_EFFECT(multinexus_backlight)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static HSV multinexus_backlight_math(HSV hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick) {
    uint16_t effect = tick - dist;
    if (effect > 255) effect = 255;
    if (dist > 50) effect = 255;
    if ((dx > 8 || dx < -8) && (dy > 8 || dy < -8)) effect = 255;
    if ((effect == 255) && (hsv.h != rgb_matrix_config.hsv.h)) {
      //hsv.v = 100;
      //hsv.h = rgb_matrix_config.hsv.h + dy / 4;
        hsv.h	= abs(rgb_matrix_config.hsv.h - 78);
    } else {
        hsv.v = qadd8(hsv.v, 255 - effect);
        hsv.h = rgb_matrix_config.hsv.h;// + dy / 4;
      //hsv.h	= 206;
    }
    if (hsv.v <= 85){
      //hsv.h = rgb_matrix_config.hsv.h + dy / 4;
        hsv.h	= abs(rgb_matrix_config.hsv.h - 78);
    }
    return hsv;
}

bool multinexus_backlight_runner(uint8_t start, effect_params_t* params, reactive_splash_f effect_func) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    uint8_t count = g_last_hit_tracker.count;
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        HSV hsv = rgb_matrix_config.hsv;
        hsv.v   = 80;
        hsv.h	= abs(rgb_matrix_config.hsv.h - 78);
        for (uint8_t j = start; j < count; j++) {
            int16_t  dx   = g_led_config.point[i].x - g_last_hit_tracker.x[j];
            int16_t  dy   = g_led_config.point[i].y - g_last_hit_tracker.y[j];
            uint8_t  dist = sqrt16(dx * dx + dy * dy);
            uint16_t tick = scale16by8(g_last_hit_tracker.tick[j], qadd8(rgb_matrix_config.speed, 1));
            hsv           = effect_func(hsv, dx, dy, dist, tick);
        }
        hsv.v   = scale8(hsv.v, rgb_matrix_config.hsv.v);
        RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
    return led_max < RGB_MATRIX_LED_COUNT;
}

static bool multinexus_backlight(effect_params_t* params) {
    return multinexus_backlight_runner(0, params, &multinexus_backlight_math);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
