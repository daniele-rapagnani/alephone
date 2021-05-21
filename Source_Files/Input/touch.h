//
// Created by Daniele Rapagnani on 2019-07-28.
//

#ifndef ALEPHONE_TOUCH_H
#define ALEPHONE_TOUCH_H

#include <cmath>
#include "cstypes.h"

#define MAX_TOUCHES 10

struct touch_config
{
    float weapon_switch_gesture_time = 300.0f;
    float weapon_switch_gesture_dist = 50.0f;
    float open_map_gesture_time = 300.0f;
    float open_map_gesture_dist = 50.0f;
};

struct touch_info
{
    float normalizedX = 0.0f;
    float normalizedY = 0.0f;
    float screenX = 0.0f;
    float screenY = 0.0f;
    float screenStartX = std::nanf("");
    float screenStartY = std::nanf("");
    float lastScreenDeltaX = 0.0f;
    float lastScreenDeltaY = 0.0f;
    Uint32 startTime = 0;
    Uint32 lastTime = 0;
    bool active = true;
};

void initialize_touch(const touch_config& config);
void add_touch(Uint8 touchId);
int process_touches(int flags);
int process_touches_terminal(int flags);
int process_touches_map(int flags);
bool touch_in_cell(const touch_info& touch, Uint8 x, Uint8 y);
void move_touch_normalized(Uint8 touchId, float x, float y);
void for_each_touch(std::function<void(touch_info* ti)> f);
touch_info* get_touch_info(Uint8 touchId);
bool remove_touch(Uint8 touchId);
void remove_all_touches();

#endif //ALEPHONE_TOUCH_H
