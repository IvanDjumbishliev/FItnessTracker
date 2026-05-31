#include "BaseEntity.h"

#include <iomanip>
#include <random>
#include <sstream>

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

} // namespace fitness
