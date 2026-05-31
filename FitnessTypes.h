#ifndef FITNESS_TYPES_H
#define FITNESS_TYPES_H

namespace fitness
{
    enum class GoalType
    {
        STRENGTH,
        CARDIO,
        WEIGHT_LOSS,
        FLEXIBILITY
    };

    enum class MuscleGroup
    {
        LEGS,
        CHEST,
        BACK,
        SHOULDERS,
        ARMS,
        CORE
    };

    enum class ExerciseCategory
    {
        STRENGTH,
        CARDIO,
        STRETCHING
    };

    enum class IntensityLevel
    {
        LOW,
        MEDIUM,
        HIGH
    };
}

#endif // FITNESS_TYPES_H
