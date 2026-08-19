#include "container.hpp"

// Includes from standard


// Includes from third party libraries


// Includes from personal libraries


// Includes from project


// Forward declarations


// Type aliases


NLUI::Container::~Container() = default;

void NLUI::Container::doLayout(const bool force) {
    doLayout(force, force);
}