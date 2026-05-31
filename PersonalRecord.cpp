#include "PersonalRecord.h"

namespace fitness
{

    PersonalRecord::PersonalRecord(std::shared_ptr<Exercise> exercise,
                                   double value,
                                   std::string unit,
                                   std::chrono::system_clock::time_point achievedAt)
        : BaseEntity(),
          exercise(std::move(exercise)),
          value(value),
          unit(std::move(unit)),
          achievedAt(achievedAt)
    {
    }

    const std::shared_ptr<Exercise> &PersonalRecord::getExercise() const noexcept
    {
        return exercise;
    }

    double PersonalRecord::getValue() const noexcept
    {
        return value;
    }

    const std::string &PersonalRecord::getUnit() const noexcept
    {
        return unit;
    }

    const std::chrono::system_clock::time_point &PersonalRecord::getAchievedAt() const noexcept
    {
        return achievedAt;
    }

    bool PersonalRecord::isBeatenBy(const PersonalRecord &newPr) const noexcept
    {
        if (!exercise || !newPr.exercise)
        {
            return false;
        }

        if (exercise->getId() != newPr.exercise->getId())
        {
            return false;
        }

        if (unit != newPr.unit)
        {
            return false;
        }

        return newPr.value > value;
    }

} // namespace fitness
