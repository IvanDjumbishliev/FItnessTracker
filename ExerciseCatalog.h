#ifndef EXERCISE_CATALOG_H
#define EXERCISE_CATALOG_H

#include "Exercise.h"

#include <memory>
#include <shared_mutex>
#include <string>
#include <vector>

namespace fitness
{
    class ExerciseCatalog
    {
    public:
        static ExerciseCatalog &getInstance();

        std::vector<std::shared_ptr<Exercise>> getByMuscleGroup(MuscleGroup muscleGroup) const;
        std::vector<std::shared_ptr<Exercise>> getByCategory(ExerciseCategory category) const;
        std::vector<std::shared_ptr<Exercise>> searchByName(const std::string &query) const;

        ExerciseCatalog(const ExerciseCatalog &) = delete;
        ExerciseCatalog &operator=(const ExerciseCatalog &) = delete;
        ExerciseCatalog(ExerciseCatalog &&) = delete;
        ExerciseCatalog &operator=(ExerciseCatalog &&) = delete;

    private:
        ExerciseCatalog();

        std::vector<std::shared_ptr<Exercise>> exercises;
        mutable std::shared_mutex mutex;
    };
}

#endif // EXERCISE_CATALOG_H
