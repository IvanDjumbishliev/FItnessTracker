#include "FitnessModule.h"
#include <iostream>

int main()
{
    try
    {
        fitness::User user("Ivan", "ivan@example.com", 82.5, 180, fitness::GoalType::STRENGTH);
        std::cout << "User created: " << user.getUsername() << " (" << user.getEmail() << ")\n";

        auto workout = user.createWorkout("Leg Day", 60, "Heavy lower-body session.");
        std::cout << "Workout created: " << workout->getName() << " for " << workout->getDurationMin() << " minutes\n";

        auto exercise = std::make_shared<fitness::StrengthExercise>("Barbell Back Squat", fitness::MuscleGroup::LEGS, "Barbell");
        std::cout << "Exercise created: " << exercise->getName() << " using " << exercise->getEquipment() << "\n";

        exercise->addSet(fitness::Set(1, 5, 100.0, false));
        exercise->addSet(fitness::Set(2, 5, 105.0, false));
        exercise->addSet(fitness::Set(3, 5, 110.0, false));
        std::cout << "Added 3 sets to exercise.\n";

        workout->addExercise(exercise);
        std::cout << "Exercise added to workout.\n";

        std::cout << "Attempting invalid set creation...\n";
        try
        {
            fitness::Set invalidSet(4, 5, -20.0, false);
            (void)invalidSet;
        }
        catch (const std::invalid_argument &error)
        {
            std::cout << "Validation caught: " << error.what() << "\n";
        }
    }
    catch (const std::exception &error)
    {
        std::cerr << "Error: " << error.what() << "\n";
        return 1;
    }

    std::cout << "Demo finished successfully.\n";
    return 0;
}
