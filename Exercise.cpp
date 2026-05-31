#include "Exercise.h"

#include <stdexcept>

namespace fitness
{

    Exercise::Exercise(std::string name,
                       MuscleGroup muscleGroup,
                       ExerciseCategory category)
        : BaseEntity(),
          name(std::move(name)),
          muscleGroup(muscleGroup),
          category(category)
    {
    }

    const std::string &Exercise::getName() const noexcept
    {
        return name;
    }

    MuscleGroup Exercise::getMuscleGroup() const noexcept
    {
        return muscleGroup;
    }

    ExerciseCategory Exercise::getCategory() const noexcept
    {
        return category;
    }

    Set::Set(int setNumber, int reps, double weightKg, bool isWarmup)
        : setNumber(setNumber),
          reps(0),
          weightKg(0.0),
          isWarmup(isWarmup)
    {
        setReps(reps);
        setWeightKg(weightKg);
    }

    int Set::getSetNumber() const noexcept
    {
        return setNumber;
    }

    int Set::getReps() const noexcept
    {
        return reps;
    }

    double Set::getWeightKg() const noexcept
    {
        return weightKg;
    }

    bool Set::getIsWarmup() const noexcept
    {
        return isWarmup;
    }

    void Set::setReps(int reps)
    {
        if (reps <= 0)
        {
            throw std::invalid_argument("reps must be greater than 0");
        }
        this->reps = reps;
    }

    void Set::setWeightKg(double weightKg)
    {
        if (weightKg <= 0.0)
        {
            throw std::invalid_argument("weightKg must be greater than 0");
        }
        this->weightKg = weightKg;
    }

    StrengthExercise::StrengthExercise(std::string name,
                                       MuscleGroup muscleGroup,
                                       std::string equipment)
        : Exercise(std::move(name), muscleGroup, ExerciseCategory::STRENGTH),
          equipment(std::move(equipment))
    {
    }

    const std::string &StrengthExercise::getEquipment() const noexcept
    {
        return equipment;
    }

    void StrengthExercise::addSet(const Set &s)
    {
        sets.push_back(s);
    }

    const std::vector<Set> &StrengthExercise::getSets() const noexcept
    {
        return sets;
    }

    double StrengthExercise::calculateCalories()
    {
        return 75.0;
    }

    CardioExercise::CardioExercise(std::string name,
                                   MuscleGroup muscleGroup,
                                   double distanceKm,
                                   int avgHeartRate,
                                   int durationMin)
        : Exercise(std::move(name), muscleGroup, ExerciseCategory::CARDIO),
          distanceKm(distanceKm),
          avgHeartRate(avgHeartRate),
          durationMin(durationMin)
    {
    }

    double CardioExercise::getPace() const noexcept
    {
        return distanceKm > 0.0 ? static_cast<double>(durationMin) / distanceKm : 0.0;
    }

    double CardioExercise::calculateCalories()
    {
        return distanceKm * 50.0 + avgHeartRate * durationMin * 0.02;
    }

    double CardioExercise::getDistanceKm() const noexcept
    {
        return distanceKm;
    }

    int CardioExercise::getAvgHeartRate() const noexcept
    {
        return avgHeartRate;
    }

    int CardioExercise::getDurationMin() const noexcept
    {
        return durationMin;
    }

    StretchingExercise::StretchingExercise(std::string name,
                                           MuscleGroup muscleGroup,
                                           int durationSec,
                                           IntensityLevel intensity)
        : Exercise(std::move(name), muscleGroup, ExerciseCategory::STRETCHING),
          durationSec(durationSec),
          intensity(intensity)
    {
    }

    int StretchingExercise::getDurationSec() const noexcept
    {
        return durationSec;
    }

    IntensityLevel StretchingExercise::getIntensity() const noexcept
    {
        return intensity;
    }

    double StretchingExercise::calculateCalories()
    {
        double intensityFactor = 1.0;
        switch (intensity)
        {
        case IntensityLevel::LOW:
            intensityFactor = 1.0;
            break;
        case IntensityLevel::MEDIUM:
            intensityFactor = 1.8;
            break;
        case IntensityLevel::HIGH:
            intensityFactor = 2.5;
            break;
        }
        return durationSec / 60.0 * intensityFactor * 4.0;
    }

} // namespace fitness
