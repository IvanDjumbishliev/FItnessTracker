#ifndef FITNESS_MODULE_H
#define FITNESS_MODULE_H

#include <chrono>
#include <memory>
#include <string>
#include <vector>

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

    class WorkoutSession;

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

    class WorkoutSession : public BaseEntity
    {
    private:
        std::string name;
        std::chrono::system_clock::time_point date;
        int durationMin;
        std::string notes;

    public:
        WorkoutSession(std::string name,
                       std::chrono::system_clock::time_point date,
                       int durationMin,
                       std::string notes);

        const std::string &getName() const noexcept;
        const std::chrono::system_clock::time_point &getDate() const noexcept;
        int getDurationMin() const noexcept;
        const std::string &getNotes() const noexcept;
    };

    class User : public BaseEntity
    {
    private:
        std::string username;
        std::string email;
        double weightKg;
        int heightCm;
        GoalType goal;

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

    private:
        std::vector<std::shared_ptr<WorkoutSession>> sessions;
    };

} // namespace fitness

#endif // FITNESS_MODULE_H
