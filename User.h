#ifndef USER_H
#define USER_H

#include "BaseEntity.h"
#include "FitnessTypes.h"

#include <memory>
#include <string>
#include <vector>

namespace fitness
{
    class WorkoutSession;

    class User : public BaseEntity
    {
    private:
        std::string username;
        std::string email;
        double weightKg;
        int heightCm;
        GoalType goal;
        std::vector<std::shared_ptr<WorkoutSession>> sessions;

    public:
        User(std::string username,
             std::string email,
             double weightKg,
             int heightCm,
             GoalType goal);

        const std::string &getUsername() const noexcept;
        void setUsername(std::string username);

        const std::string &getEmail() const noexcept;
        void setEmail(std::string email);

        double getWeightKg() const noexcept;
        void setWeightKg(double weightKg);

        int getHeightCm() const noexcept;
        void setHeightCm(int heightCm);

        GoalType getGoal() const noexcept;
        void setGoal(GoalType goal);

        std::shared_ptr<WorkoutSession> createWorkout(const std::string &name,
                                                      int durationMin,
                                                      const std::string &notes);
    };
}

#endif // USER_H
