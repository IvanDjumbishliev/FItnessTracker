#include "FitnessModule.h"

#include <iomanip>
#include <random>
#include <sstream>
#include <stdexcept>

namespace fitness
{

    namespace
    {

        std::string generateId()
        {
            static std::random_device rd;
            static std::mt19937_64 gen(rd());
            static std::uniform_int_distribution<unsigned long long> dist(0, 0xFFFFFFFFFFFFFFFFULL);

            std::ostringstream oss;
            oss << std::hex << std::setw(16) << std::setfill('0') << dist(gen);
            return oss.str();
        }

    } // namespace

    BaseEntity::BaseEntity()
        : id(generateId()),
          createdAt(std::chrono::system_clock::now()),
          updatedAt(createdAt)
    {
    }

    BaseEntity::~BaseEntity() = default;

    const std::string &BaseEntity::getId() const noexcept
    {
        return id;
    }

    const std::chrono::system_clock::time_point &BaseEntity::getCreatedAt() const noexcept
    {
        return createdAt;
    }

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

    WorkoutSession::WorkoutSession(std::string name,
                                   std::chrono::system_clock::time_point date,
                                   int durationMin,
                                   std::string notes)
        : BaseEntity(),
          name(std::move(name)),
          date(date),
          durationMin(durationMin),
          notes(std::move(notes))
    {
    }

    const std::string &WorkoutSession::getName() const noexcept
    {
        return name;
    }

    const std::chrono::system_clock::time_point &WorkoutSession::getDate() const noexcept
    {
        return date;
    }

    int WorkoutSession::getDurationMin() const noexcept
    {
        return durationMin;
    }

    const std::string &WorkoutSession::getNotes() const noexcept
    {
        return notes;
    }

    void WorkoutSession::addExercise(std::shared_ptr<Exercise> e)
    {
        exercises.push_back(std::move(e));
    }

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
