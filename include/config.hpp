/*
 * Created by okn-yu on 2022/05/05.
 */

#ifndef PRACTICEPATHTRACING_CONFIG_H
#define PRACTICEPATHTRACING_CONFIG_H

struct ConstParam
{
    //float HIT_DISTANCE_MAX = 10000;
    //float HIT_DISTANCE_MIN = 0;
    constexpr static const double RAY_T_MAX = 100;
    constexpr static const float GAMMA_VALUE = 1.8;
};

#endif //PRACTICEPATHTRACING_CONFIG_H
