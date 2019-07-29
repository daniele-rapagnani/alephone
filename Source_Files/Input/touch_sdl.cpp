//
// Created by Daniele Rapagnani on 2019-07-28.
//

#include <SDL.h>

#include "screen.h"
#include "player.h"
#include "touch.h"

static touch_info* touches[MAX_TOUCHES];
static touch_config config = {};
static SDL_DisplayMode display_mode = {};
static SDL_Rect virtual_screen_size = {};

void initialize_touch(const touch_config& config)
{
    ::config = config;

    SDL_GetCurrentDisplayMode(0, &display_mode);

    int wheight = alephone::Screen::instance()->window_height();
    double screenRatio = static_cast<double>(display_mode.w) / display_mode.h;

    virtual_screen_size.w = wheight * screenRatio;
    virtual_screen_size.h = wheight;
}

void add_touch(Uint8 touchId)
{
    if (touchId >= MAX_TOUCHES)
    {
        return;
    }

    if (touches[touchId])
    {
        return;
    }

    touches[touchId] = new touch_info();
}

void move_touch_normalized(Uint8 touchId, float x, float y)
{
    touch_info* info = get_touch_info(touchId);

    if (!info)
    {
        return;
    }

    info->normalizedX = x;
    info->normalizedY = y;

    alephone::Screen* s = alephone::Screen::instance();

    int wwidth = s->window_width();
    int wheight = s->window_height();

    double screenX = x * wwidth;
    double screenY = y * wheight;

    double xScale = virtual_screen_size.w / wwidth;

    screenX += ((wwidth * xScale) - wwidth) * 0.5;

    info->screenX = screenX;
    info->screenY = screenY;

    info->lastTime = SDL_GetTicks();

    if (isnanf(info->screenStartX))
    {
        info->screenStartX = info->screenX;
        info->screenStartY = info->screenY;
    }

    if (info->startTime == 0)
    {
        info->startTime = info->lastTime;
    }
}

touch_info* get_touch_info(Uint8 touchId)
{
    if (touchId >= MAX_TOUCHES)
    {
        return nullptr;
    }

    return touches[touchId];
}

bool remove_touch(Uint8 touchId)
{
    if (touchId >= MAX_TOUCHES)
    {
        return false;
    }

    if (!touches[touchId])
    {
        return false;
    }

    delete touches[touchId];
    touches[touchId] = nullptr;

    return true;
}

int process_touches()
{
    int flags = 0;

    for (Uint8 i = 0; i < MAX_TOUCHES; i++)
    {
        if (!touches[i] || !touches[i]->active)
        {
            continue;
        }

        touch_info* ti = touches[i];

        float ydist = std::fabsf(ti->screenY - ti->screenStartY);
        float xdist = std::fabsf(ti->screenX - ti->screenStartX);

        float ysign = ti->screenY < ti->screenStartY ? -1.0f : 1.0f;
        float xsign = ti->screenX < ti->screenStartX ? -1.0f : 1.0f;

        float timeElapsed = static_cast<float>(ti->lastTime) - ti->startTime;

        if (
            ti->screenStartX > virtual_screen_size.w * 0.66f
            && ti->screenStartY > virtual_screen_size.h * 0.5f
        )
        {
            if (ydist > config.vertical_dead_zone_px)
            {
                flags |= ysign < 0 ? _moving_forward : _moving_backward;
            }

            if (xdist > config.horizontal_dead_zone_px)
            {
                flags |= xsign < 0 ? _turning_left : _turning_right;
            }
        }
        else if(
            ti->screenStartX < virtual_screen_size.w * 0.33f
            && ti->screenStartY > virtual_screen_size.h * 0.5f
        )
        {
            flags |= _left_trigger_state;
        }
        else if(
                ti->screenStartX < virtual_screen_size.w * 0.33f
                && ti->screenStartY < virtual_screen_size.h * 0.5f
                )
        {
            flags |= _right_trigger_state;
        }
        else if(
            ti->screenStartX > virtual_screen_size.w * 0.33f
            && ti->screenStartX < virtual_screen_size.w * 0.66f
            && ti->screenStartY < virtual_screen_size.h * 0.5f
        )
        {
            if (
                xdist > config.weapon_switch_gesture_dist
                && timeElapsed < config.weapon_switch_gesture_time
            )
            {
                flags |= xsign < 0.0f ? _cycle_weapons_backward : _cycle_weapons_forward;
                ti->active = false;
            }
            else if (
                ydist > config.open_map_gesture_dist
                && timeElapsed < config.open_map_gesture_time
                && ysign > 0.0f
            )
            {
                flags |= _toggle_map;
                ti->active = false;
            }
        }
        else if(
                ti->screenStartX > virtual_screen_size.w * 0.33f
                && ti->screenStartX < virtual_screen_size.w * 0.66f
                && ti->screenStartY > virtual_screen_size.h * 0.5f
                )
        {
            flags |= _action_trigger_state;
            ti->active = false;
        }
    }

    return flags;
}

int process_touches_terminal()
{
    int flags = 0;

    for (Uint8 i = 0; i < MAX_TOUCHES; i++)
    {
        if (!touches[i] || !touches[i]->active)
        {
            continue;
        }

        touch_info* ti = touches[i];

        if (ti->screenStartX < virtual_screen_size.w * 0.5f)
        {
            flags |= _turning_left;
        }
        else
        {
            flags |= _turning_right;
        }

        ti->active = false;
    }

    return flags;
}

int process_touches_map()
{
    int flags = 0;

    for (Uint8 i = 0; i < MAX_TOUCHES; i++)
    {
        if (!touches[i] || !touches[i]->active)
        {
            continue;
        }
    }

    return flags;
}

void remove_all_touches()
{
    for (Uint8 i = 0; i < MAX_TOUCHES; i++)
    {
        if (touches[i])
        {
            delete touches[i];
            touches[i] = nullptr;
        }
    }
}
