#ifndef WEEKLY_SUMMARY_H
#define WEEKLY_SUMMARY_H

#include "WorkoutSession.h"

#include <chrono>
#include <memory>
#include <vector>

namespace fitness
{
    class WeeklySummary
    {
    public:
        WeeklySummary(std::chrono::system_clock::time_point startDate,
                      std::chrono::system_clock::time_point endDate,
                      std::vector<std::shared_ptr<WorkoutSession>> sessions,
                      std::shared_ptr<WeeklySummary> previousSummary = nullptr);

        std::chrono::system_clock::time_point getStartDate() const noexcept;
        std::chrono::system_clock::time_point getEndDate() const noexcept;
        const std::vector<std::shared_ptr<WorkoutSession>> &getSessions() const noexcept;
        std::shared_ptr<WeeklySummary> getPreviousSummary() const noexcept;

        std::size_t getTotalWorkouts() const noexcept;
        double getTotalCalories() const noexcept;
        double getTotalVolume() const noexcept;
        double getProgressVsPrevious() const noexcept;

    private:
        std::chrono::system_clock::time_point startDate;
        std::chrono::system_clock::time_point endDate;
        std::vector<std::shared_ptr<WorkoutSession>> sessions;
        std::shared_ptr<WeeklySummary> previousSummary;
    };
}

#endif // WEEKLY_SUMMARY_H
