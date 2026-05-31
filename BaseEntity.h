#ifndef BASE_ENTITY_H
#define BASE_ENTITY_H

#include "FitnessTypes.h"
#include <chrono>
#include <string>

namespace fitness
{
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
}

#endif // BASE_ENTITY_H
