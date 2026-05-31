#include "WorkoutSession.h"

namespace fitness
{

    WorkoutSession::WorkoutSession(std::string name,
                                   std::chrono::system_clock::time_point date,
                                   int durationMin,
                                   std::string notes)
        : BaseEntity(),
          name(std::move(name)),
          date(date),
          durationMin(durationMin),
          notes(std::move(notes))
    {
    }

    const std::string &WorkoutSession::getName() const noexcept
    {
        return name;
    }

    const std::chrono::system_clock::time_point &WorkoutSession::getDate() const noexcept
    {
        return date;
    }

    int WorkoutSession::getDurationMin() const noexcept
    {
        return durationMin;
    }

    const std::string &WorkoutSession::getNotes() const noexcept
    {
        return notes;
    }

    void WorkoutSession::addExercise(std::shared_ptr<Exercise> e)
    {
        exercises.push_back(std::move(e));
    }

} // namespace fitness
