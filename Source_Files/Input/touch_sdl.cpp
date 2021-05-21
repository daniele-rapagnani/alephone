//
// Created by Daniele Rapagnani on 2019-07-28.
//

#include <SDL.h>

#include "cseries.h"
#include "screen.h"
#include "player.h"
#include "touch.h"
#include "preferences.h"

static touch_info* touches[MAX_TOUCHES];
static touch_config config = {};
static SDL_DisplayMode display_mode = {};
static SDL_Rect virtual_screen_size = {};
static touch_info* action_touch = nullptr;

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

    double xScale = static_cast<double>(virtual_screen_size.w) / wwidth;

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

    if (action_touch && touches[touchId] == action_touch)
    {
        action_touch = nullptr;
    }

    delete touches[touchId];
    touches[touchId] = nullptr;

    return true;
}

bool touch_in_cell(const touch_info& touch, Uint8 x, Uint8 y)
{
    float left = 0.0f;
    float right = 1.0f;
    float top = 0.0f;
    float bottom = 0.0f;

    switch(x)
    {
        case 0:
            left = 0.0f;
            right = input_preferences->touch_zone_left / 100.0f;
            break;

        case 1:
            left = input_preferences->touch_zone_left / 100.0f;
            right = input_preferences->touch_zone_right / 100.0f;
            break;

        case 2:
            left = input_preferences->touch_zone_right / 100.0f;
            right = 1.0f;
            break;

        default:
            return false;
    }

    switch(y)
    {
        case 0:
            top = 0.0f;
            bottom = input_preferences->touch_zone_top / 100.0f;
            break;

        case 1:
            top = input_preferences->touch_zone_top / 100.0f;
            bottom = input_preferences->touch_zone_bottom / 100.0f;
            break;

        case 2:
            top = input_preferences->touch_zone_bottom / 100.0f;
            bottom = 1.0f;
            break;

        default:
            return false;
    }

    return
        touch.screenStartX >= virtual_screen_size.w * left
        && touch.screenStartX < virtual_screen_size.w * right
        && touch.screenStartY >= virtual_screen_size.h * top
        && touch.screenStartY < virtual_screen_size.h * bottom
    ;
}

int process_touches(int flags)
{
    for_each_touch([&flags] (touch_info* ti) {
        float ydist = std::fabsf(ti->screenY - ti->screenStartY);
        float xdist = std::fabsf(ti->screenX - ti->screenStartX);

        float ysign = ti->screenY < ti->screenStartY ? -1.0f : 1.0f;
        float xsign = ti->screenX < ti->screenStartX ? -1.0f : 1.0f;

        float timeElapsed = static_cast<float>(ti->lastTime) - ti->startTime;

        if (touch_in_cell(*ti, 2, 2))
        {
            float yaw = 0.0f;
            float pitch = 0.0f;

            if (ydist > input_preferences->touch_vertical_deadzone)
            {
                if (action_touch)
                {
                    pitch = (ydist - input_preferences->touch_vertical_deadzone)
                        / input_preferences->touch_pitch_zone_size * -ysign
                    ;
                }
                else
                {
                    flags |= ysign < 0 ? _moving_forward : _moving_backward;
                }
            }

            if (xdist > input_preferences->touch_horizontal_deadzone)
            {
                yaw = (xdist - input_preferences->touch_horizontal_deadzone)
                    / input_preferences->touch_yaw_zone_size * xsign
                ;
            }

            const fixed_angle dyaw = static_cast<fixed_angle>(yaw * FIXED_ONE);
            const fixed_angle dpitch = static_cast<fixed_angle>(pitch * FIXED_ONE);

            if (dyaw != 0 || dpitch != 0)
            {
                flags = process_aim_input(flags, {dyaw, dpitch});
            }
        }
        else if(touch_in_cell(*ti, 0, 2))
        {
            flags |= _left_trigger_state;
        }
        else if(touch_in_cell(*ti, 0, 0))
        {
            flags |= _right_trigger_state;
        }
        else if(touch_in_cell(*ti, 1, 0))
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
        else if(touch_in_cell(*ti, 1, 2))
        {
            if (action_touch && action_touch != ti)
            {
                flags |= _looking_center;
            }
            else
            {
                flags |= _action_trigger_state;
                action_touch = ti;
            }

            ti->active = false;
        }
        else if (touch_in_cell(*ti, 2, 0))
        {
            flags |= _swim;
        }
    });

    return flags;
}

int process_touches_terminal(int flags)
{
    for_each_touch([&flags] (touch_info* ti) {
        if (ti->screenStartX < virtual_screen_size.w * 0.5f)
        {
            flags |= _turning_left;
        }
        else
        {
            flags |= _turning_right;
        }

        ti->active = false;
    });

    return flags;
}

int process_touches_map(int flags)
{
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

void for_each_touch(std::function<void(touch_info* ti)> f)
{
    if (!f)
    {
        return;
    }

    for (Uint8 i = 0; i < MAX_TOUCHES; i++)
    {
        if (!touches[i] || !touches[i]->active)
        {
            continue;
        }

        f(touches[i]);
    }
}
