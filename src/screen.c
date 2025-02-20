#include "warpd.h"

void screen_selection_mode()
{
	size_t i;
	size_t n;
	screen_t screens[MAX_SCREENS];
	struct input_event *ev;
	const char *screen_chars = config_get("screen_chars");

	screen_list(screens, &n);
	assert(strlen(screen_chars) >= n);

	for (i = 0; i < n; i++) {
		struct hint hint;
		int w, h;
		screen_get_dimensions(screens[i], &w, &h);

		hint.x = w / 2 - 25;
		hint.y = h / 2 - 25;
		hint.w = 50;
		hint.h = 50;

		hint.label[0] = screen_chars[i];
		hint.label[1] = 0;

		hint_draw(screens[i], &hint, 1);
	}

	platform_commit();

	input_grab_keyboard();
	while (1) {
		ev = input_next_event(0);
		if (ev->pressed)
			break;
	}
	input_ungrab_keyboard();

	for (i = 0; i < n; i++) {
		const char *key = input_event_tostr(ev);

		if (key[0] == screen_chars[i] && key[1] == 0) {
			int w, h;
			screen_get_dimensions(screens[i], &w, &h);
			mouse_move(screens[i], w/2, h/2);
		}
	}

	for (i = 0; i < n; i++)
		screen_clear(screens[i]);

	platform_commit();
}
