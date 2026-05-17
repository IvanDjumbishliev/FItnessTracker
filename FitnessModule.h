#ifndef FITNESS_MODULE_H
#define FITNESS_MODULE_H

#include <chrono>
#include <memory>
#include <stdexcept>
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

    class Exercise;
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

    class Exercise : public BaseEntity
    {
    protected:
        std::string name;
        MuscleGroup muscleGroup;
        ExerciseCategory category;

        Exercise(std::string name,
                 MuscleGroup muscleGroup,
                 ExerciseCategory category);

    public:
        virtual ~Exercise() = default;

        const std::string &getName() const noexcept;
        MuscleGroup getMuscleGroup() const noexcept;
        ExerciseCategory getCategory() const noexcept;

        virtual double calculateCalories() = 0;
    };

    class Set
    {
    private:
        int setNumber;
        int reps;
        double weightKg;
        bool isWarmup;

    public:
        Set(int setNumber, int reps, double weightKg, bool isWarmup);

        int getSetNumber() const noexcept;
        int getReps() const noexcept;
        double getWeightKg() const noexcept;
        bool getIsWarmup() const noexcept;

        void setReps(int reps);
        void setWeightKg(double weightKg);
    };

    class StrengthExercise : public Exercise
    {
    private:
        std::string equipment;
        std::vector<Set> sets;

    public:
        StrengthExercise(std::string name,
                         MuscleGroup muscleGroup,
                         std::string equipment);

        const std::string &getEquipment() const noexcept;
        void addSet(const Set &s);
        double calculateCalories() override;
    };

    class CardioExercise : public Exercise
    {
    private:
        double distanceKm;
        int avgHeartRate;
        int durationMin;

    public:
        CardioExercise(std::string name,
                       MuscleGroup muscleGroup,
                       double distanceKm,
                       int avgHeartRate,
                       int durationMin);

        double getPace() const noexcept;
        double calculateCalories() override;
        double getDistanceKm() const noexcept;
        int getAvgHeartRate() const noexcept;
        int getDurationMin() const noexcept;
    };

    class StretchingExercise : public Exercise
    {
    private:
        int durationSec;
        IntensityLevel intensity;

    public:
        StretchingExercise(std::string name,
                           MuscleGroup muscleGroup,
                           int durationSec,
                           IntensityLevel intensity);

        int getDurationSec() const noexcept;
        IntensityLevel getIntensity() const noexcept;
        double calculateCalories() override;
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

        void addExercise(std::shared_ptr<Exercise> e);

    private:
        std::vector<std::shared_ptr<Exercise>> exercises;
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
