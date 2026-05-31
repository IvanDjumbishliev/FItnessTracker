#include "FitnessModule.h"
#include <iomanip>
#include <iostream>

int main()
{
    std::cout << "========================" << std::endl;
    std::cout << " Fitness Tracker Demo " << std::endl;
    std::cout << "========================\n"
              << std::endl;

    try
    {
        std::cout << "1) Create user profile" << std::endl;
        fitness::User user("Ivan", "ivan@example.com", 82.5, 180, fitness::GoalType::STRENGTH);
        std::cout << "   Profile: " << user.getUsername() << " | " << user.getEmail() << " | " << user.getWeightKg() << "kg | " << user.getHeightCm() << "cm\n"
                  << std::endl;

        std::cout << "2) Explore exercise catalog" << std::endl;
        auto &catalog = fitness::ExerciseCatalog::getInstance();

        std::cout << "   Strength exercises:" << std::endl;
        for (const auto &exercise : catalog.getByCategory(fitness::ExerciseCategory::STRENGTH))
        {
            std::cout << "   - " << exercise->getName() << " (" << static_cast<int>(exercise->getMuscleGroup()) << ")\n";
        }

        std::cout << "\n   Search exercises containing 'Run':" << std::endl;
        for (const auto &exercise : catalog.searchByName("Run"))
        {
            std::cout << "   - " << exercise->getName() << "\n";
        }

        std::cout << "\n3) Create first workout with strength sets" << std::endl;
        auto workoutA = user.createWorkout("Leg Day", 60, "Heavy lower-body session");
        auto squat = std::make_shared<fitness::StrengthExercise>("Barbell Back Squat", fitness::MuscleGroup::LEGS, "Barbell");
        squat->addSet(fitness::Set(1, 8, 80.0, true));
        squat->addSet(fitness::Set(2, 5, 100.0, false));
        squat->addSet(fitness::Set(3, 3, 110.0, false));
        workoutA->addExercise(squat);
        std::cout << "   Workout created: " << workoutA->getName() << " with " << squat->getName() << "\n"
                  << std::endl;

        std::cout << "4) Complete workout and record PRs" << std::endl;
        user.completeWorkout(workoutA);
        for (const auto &record : user.getPersonalRecords())
        {
            std::cout << "   PR recorded: " << record.getExercise()->getName() << " - " << record.getValue() << record.getUnit() << " at " << record.getAchievedAt().time_since_epoch().count() << "\n";
        }

        std::cout << "\n5) Create improved workout to beat PR" << std::endl;
        auto workoutB = user.createWorkout("Back Squat PR", 55, "Attempt heavier back squat");
        auto squatPr = std::make_shared<fitness::StrengthExercise>("Barbell Back Squat", fitness::MuscleGroup::LEGS, "Barbell");
        squatPr->addSet(fitness::Set(1, 5, 105.0, false));
        squatPr->addSet(fitness::Set(2, 3, 115.0, false));
        workoutB->addExercise(squatPr);
        user.completeWorkout(workoutB);

        std::cout << "   Updated PRs:" << std::endl;
        for (const auto &record : user.getPersonalRecords())
        {
            std::cout << "   - " << record.getExercise()->getName() << ": " << record.getValue() << record.getUnit() << "\n";
        }

        std::cout << "\n6) Generate weekly summary" << std::endl;
        auto summary = user.getWeeklySummary();
        std::cout << "   Total workouts: " << summary.getTotalWorkouts() << "\n";
        std::cout << "   Total calories: " << std::fixed << std::setprecision(1) << summary.getTotalCalories() << " kcal\n";
        std::cout << "   Total volume: " << std::fixed << std::setprecision(1) << summary.getTotalVolume() << " kg*reps\n";
        std::cout << "   Progress vs previous week: " << std::fixed << std::setprecision(1) << summary.getProgressVsPrevious() << "%\n"
                  << std::endl;

        std::cout << "7) Export workout history to CSV" << std::endl;
        const std::string filename = "workout_history.csv";
        if (user.exportWorkoutHistory(filename))
        {
            std::cout << "   Export successful: " << filename << "\n";
        }
        else
        {
            std::cout << "   Export failed: " << filename << "\n";
        }

        std::cout << "\n8) Demo completed successfully" << std::endl;
    }
    catch (const std::exception &error)
    {
        std::cerr << "Demo error: " << error.what() << std::endl;
        return 1;
    }

    return 0;
}
