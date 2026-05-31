#ifndef WORKOUT_SESSION_H
#define WORKOUT_SESSION_H

#include "BaseEntity.h"

#include <chrono>
#include <memory>
#include <string>
#include <vector>

namespace fitness
{
    class Exercise;

    class WorkoutSession : public BaseEntity
    {
    private:
        std::string name;
        std::chrono::system_clock::time_point date;
        int durationMin;
        std::string notes;
        std::vector<std::shared_ptr<Exercise>> exercises;

    public:
        WorkoutSession(std::string name,
                       std::chrono::system_clock::time_point date,
                       int durationMin,
                       std::string notes);

        const std::string &getName() const noexcept;
        const std::chrono::system_clock::time_point &getDate() const noexcept;
        int getDurationMin() const noexcept;
        const std::string &getNotes() const noexcept;

        void addExercise(std::shared_ptr<Exercise> e);
    };
}

#endif // WORKOUT_SESSION_H
