#include "ExerciseCatalog.h"

#include <algorithm>
#include <cctype>
#include <locale>

namespace fitness
{

    ExerciseCatalog &ExerciseCatalog::getInstance()
    {
        static ExerciseCatalog instance;
        return instance;
    }

    ExerciseCatalog::ExerciseCatalog()
    {
        std::lock_guard lock(mutex);

        exercises.push_back(std::make_shared<StrengthExercise>("Back Squat", MuscleGroup::LEGS, "Barbell"));
        exercises.push_back(std::make_shared<StrengthExercise>("Push-ups", MuscleGroup::CHEST, "Bodyweight"));
        exercises.push_back(std::make_shared<CardioExercise>("Running", MuscleGroup::LEGS, 5.0, 140, 30));
        exercises.push_back(std::make_shared<StretchingExercise>("Hamstring Stretch", MuscleGroup::LEGS, 90, IntensityLevel::LOW));
    }

    std::vector<std::shared_ptr<Exercise>> ExerciseCatalog::getByMuscleGroup(MuscleGroup muscleGroup) const
    {
        std::shared_lock lock(mutex);
        std::vector<std::shared_ptr<Exercise>> result;
        result.reserve(exercises.size());

        for (const auto &exercise : exercises)
        {
            if (exercise->getMuscleGroup() == muscleGroup)
            {
                result.push_back(exercise);
            }
        }

        return result;
    }

    std::vector<std::shared_ptr<Exercise>> ExerciseCatalog::getByCategory(ExerciseCategory category) const
    {
        std::shared_lock lock(mutex);
        std::vector<std::shared_ptr<Exercise>> result;
        result.reserve(exercises.size());

        for (const auto &exercise : exercises)
        {
            if (exercise->getCategory() == category)
            {
                result.push_back(exercise);
            }
        }

        return result;
    }

    static std::string normalizeString(const std::string &text)
    {
        std::string normalized;
        normalized.reserve(text.size());

        for (unsigned char ch : text)
        {
            normalized.push_back(static_cast<char>(std::tolower(ch)));
        }

        return normalized;
    }

    std::vector<std::shared_ptr<Exercise>> ExerciseCatalog::searchByName(const std::string &query) const
    {
        std::shared_lock lock(mutex);
        std::vector<std::shared_ptr<Exercise>> result;
        const std::string normalizedQuery = normalizeString(query);

        for (const auto &exercise : exercises)
        {
            const std::string normalizedName = normalizeString(exercise->getName());
            if (normalizedName.find(normalizedQuery) != std::string::npos)
            {
                result.push_back(exercise);
            }
        }

        return result;
    }

} // namespace fitness
