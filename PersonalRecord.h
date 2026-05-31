#ifndef PERSONAL_RECORD_H
#define PERSONAL_RECORD_H

#include "BaseEntity.h"
#include "Exercise.h"

#include <chrono>
#include <memory>
#include <string>

namespace fitness
{
    class PersonalRecord : public BaseEntity
    {
    public:
        PersonalRecord(std::shared_ptr<Exercise> exercise,
                       double value,
                       std::string unit,
                       std::chrono::system_clock::time_point achievedAt);

        const std::shared_ptr<Exercise> &getExercise() const noexcept;
        double getValue() const noexcept;
        const std::string &getUnit() const noexcept;
        const std::chrono::system_clock::time_point &getAchievedAt() const noexcept;

        bool isBeatenBy(const PersonalRecord &newPr) const noexcept;

    private:
        std::shared_ptr<Exercise> exercise;
        double value;
        std::string unit;
        std::chrono::system_clock::time_point achievedAt;
    };
}

#endif // PERSONAL_RECORD_H
