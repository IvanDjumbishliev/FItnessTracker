#include "User.h"
#include "WorkoutSession.h"
#include "WeeklySummary.h"

#include <algorithm>
#include <stdexcept>

namespace fitness
{

    User::User(std::string username,
               std::string email,
               double weightKg,
               int heightCm,
               GoalType goal)
        : BaseEntity(),
          username(std::move(username)),
          email(std::move(email)),
          weightKg(0.0),
          heightCm(0),
          goal(goal)
    {
        setWeightKg(weightKg);
        setHeightCm(heightCm);
    }

    const std::string &User::getUsername() const noexcept
    {
        return username;
    }

    void User::setUsername(std::string username)
    {
        this->username = std::move(username);
    }

    const std::string &User::getEmail() const noexcept
    {
        return email;
    }

    void User::setEmail(std::string email)
    {
        this->email = std::move(email);
    }

    double User::getWeightKg() const noexcept
    {
        return weightKg;
    }

    void User::setWeightKg(double weightKg)
    {
        if (weightKg <= 0.0)
        {
            throw std::invalid_argument("weightKg must be greater than 0");
        }
        this->weightKg = weightKg;
    }

    int User::getHeightCm() const noexcept
    {
        return heightCm;
    }

    void User::setHeightCm(int heightCm)
    {
        if (heightCm <= 0)
        {
            throw std::invalid_argument("heightCm must be greater than 0");
        }
        this->heightCm = heightCm;
    }

    GoalType User::getGoal() const noexcept
    {
        return goal;
    }

    void User::setGoal(GoalType goal)
    {
        this->goal = goal;
    }

    std::shared_ptr<WorkoutSession> User::createWorkout(const std::string &name,
                                                        int durationMin,
                                                        const std::string &notes)
    {
        auto session = std::make_shared<WorkoutSession>(name,
                                                        std::chrono::system_clock::now(),
                                                        durationMin,
                                                        notes);
        sessions.push_back(session);
        return session;
    }

    const std::vector<PersonalRecord> &User::getPersonalRecords() const noexcept
    {
        return prs;
    }

    void User::completeWorkout(const std::shared_ptr<WorkoutSession> &session)
    {
        if (!session)
        {
            return;
        }

        for (const auto &exercise : session->getExercises())
        {
            auto strengthExercise = std::dynamic_pointer_cast<StrengthExercise>(exercise);
            if (!strengthExercise)
            {
                continue;
            }

            double maxWeight = 0.0;
            for (const auto &set : strengthExercise->getSets())
            {
                if (!set.getIsWarmup() && set.getWeightKg() > maxWeight)
                {
                    maxWeight = set.getWeightKg();
                }
            }

            if (maxWeight <= 0.0)
            {
                continue;
            }

            auto existing = std::find_if(prs.begin(), prs.end(), [&](const PersonalRecord &record)
                                         { return record.getExercise() && record.getExercise()->getName() == strengthExercise->getName() && record.getUnit() == "kg"; });

            PersonalRecord newRecord(strengthExercise, maxWeight, "kg", std::chrono::system_clock::now());
            if (existing == prs.end())
            {
                prs.push_back(std::move(newRecord));
            }
            else if (existing->isBeatenBy(newRecord))
            {
                *existing = std::move(newRecord);
            }
        }
    }

    WeeklySummary User::getWeeklySummary() const
    {
        using namespace std::chrono;

        auto end = system_clock::now();
        if (!sessions.empty())
        {
            auto latest = std::max_element(sessions.begin(), sessions.end(), [](const auto &lhs, const auto &rhs)
                                           {
                                               if (!lhs || !rhs)
                                               {
                                                   return rhs != nullptr;
                                               }
                                               return lhs->getDate() < rhs->getDate(); });
            if (latest != sessions.end() && *latest)
            {
                end = (*latest)->getDate();
            }
        }

        auto start = end - hours(24 * 7);
        auto previousStart = start - hours(24 * 7);
        auto previousEnd = start;

        std::vector<std::shared_ptr<WorkoutSession>> currentWeekSessions;
        std::vector<std::shared_ptr<WorkoutSession>> previousWeekSessions;

        for (const auto &session : sessions)
        {
            if (!session)
            {
                continue;
            }

            const auto &date = session->getDate();
            if (date >= start && date <= end)
            {
                currentWeekSessions.push_back(session);
            }
            else if (date >= previousStart && date < previousEnd)
            {
                previousWeekSessions.push_back(session);
            }
        }

        auto previousSummary = std::make_shared<WeeklySummary>(previousStart, previousEnd, std::move(previousWeekSessions));
        return WeeklySummary(start, end, std::move(currentWeekSessions), std::move(previousSummary));
    }

} // namespace fitness
