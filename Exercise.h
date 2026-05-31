#ifndef EXERCISE_H
#define EXERCISE_H

#include "BaseEntity.h"
#include "FitnessTypes.h"

#include <memory>
#include <string>
#include <vector>

namespace fitness
{
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
}

#endif // EXERCISE_H
