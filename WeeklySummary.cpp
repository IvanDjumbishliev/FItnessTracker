#include "WeeklySummary.h"
#include "Exercise.h"

namespace fitness
{

    WeeklySummary::WeeklySummary(std::chrono::system_clock::time_point startDate,
                                 std::chrono::system_clock::time_point endDate,
                                 std::vector<std::shared_ptr<WorkoutSession>> sessions,
                                 std::shared_ptr<WeeklySummary> previousSummary)
        : startDate(startDate),
          endDate(endDate),
          sessions(std::move(sessions)),
          previousSummary(std::move(previousSummary))
    {
    }

    std::chrono::system_clock::time_point WeeklySummary::getStartDate() const noexcept
    {
        return startDate;
    }

    std::chrono::system_clock::time_point WeeklySummary::getEndDate() const noexcept
    {
        return endDate;
    }

    const std::vector<std::shared_ptr<WorkoutSession>> &WeeklySummary::getSessions() const noexcept
    {
        return sessions;
    }

    std::shared_ptr<WeeklySummary> WeeklySummary::getPreviousSummary() const noexcept
    {
        return previousSummary;
    }

    std::size_t WeeklySummary::getTotalWorkouts() const noexcept
    {
        return sessions.size();
    }

    static double calculateSessionCalories(const std::shared_ptr<WorkoutSession> &session)
    {
        double totalCalories = 0.0;
        if (!session)
        {
            return totalCalories;
        }

        for (const auto &exercise : session->getExercises())
        {
            if (exercise)
            {
                totalCalories += exercise->calculateCalories();
            }
        }

        return totalCalories;
    }

    static double calculateSessionVolume(const std::shared_ptr<WorkoutSession> &session)
    {
        double totalVolume = 0.0;
        if (!session)
        {
            return totalVolume;
        }

        for (const auto &exercise : session->getExercises())
        {
            auto strength = std::dynamic_pointer_cast<StrengthExercise>(exercise);
            if (!strength)
            {
                continue;
            }

            for (const auto &set : strength->getSets())
            {
                totalVolume += set.getWeightKg() * set.getReps();
            }
        }

        return totalVolume;
    }

    double WeeklySummary::getTotalCalories() const noexcept
    {
        double totalCalories = 0.0;
        for (const auto &session : sessions)
        {
            totalCalories += calculateSessionCalories(session);
        }
        return totalCalories;
    }

    double WeeklySummary::getTotalVolume() const noexcept
    {
        double totalVolume = 0.0;
        for (const auto &session : sessions)
        {
            totalVolume += calculateSessionVolume(session);
        }
        return totalVolume;
    }

    double WeeklySummary::getProgressVsPrevious() const noexcept
    {
        if (!previousSummary)
        {
            return 0.0;
        }

        double previousVolume = previousSummary->getTotalVolume();
        if (previousVolume <= 0.0)
        {
            return 0.0;
        }

        double currentVolume = getTotalVolume();
        return (currentVolume - previousVolume) / previousVolume * 100.0;
    }

} // namespace fitness
