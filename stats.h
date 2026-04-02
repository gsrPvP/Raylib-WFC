#pragma once

typedef enum StatType{
    STAT_DAMAGE,
    STAT_FIRE_RATE,
    STAT_RANGE,
    STAT_FIRE_DAMAGE,
    STAT_EXP_DAMAGE,
    STAT_SLOW,
    STAT_MAX_TARGETS,

    STAT_MONEY_BONUS,
    STAT_LUCKY,

    STAT_FIRE_RESISTENCE,
    STAT_ARMOR,
    STAT_HEALTH,
    STAT_SPEED,
    MAX_STATS
}StatType;

typedef struct{
    float value[MAX_STATS];
}Stats;

