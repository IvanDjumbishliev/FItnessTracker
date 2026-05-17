#ifndef FITNESS_MODULE_H
#define FITNESS_MODULE_H

#include <chrono>
#include <string>

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

    class BaseEntity
    {
    protected:
        std::string id;
        std::chrono::system_clock::time_point createdAt;
        std::chrono::system_clock::time_point updatedAt;

    public:
        BaseEntity();
        virtual ~BaseEntity();

        const std::string &getId() const noexcept;
        const std::chrono::system_clock::time_point &getCreatedAt() const noexcept;
    };

} // namespace fitness

#endif // FITNESS_MODULE_H
