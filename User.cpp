#include "User.h"
#include "WorkoutSession.h"

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

} // namespace fitness
