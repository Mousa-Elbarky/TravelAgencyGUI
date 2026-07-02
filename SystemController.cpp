#include "SystemController.h"

double SystemController::totalCost = 0.0;
std::string SystemController::selectedCountry = "";
std::string SystemController::selectedActivity = "";
std::string SystemController::activityTime = "";

FlightSystem SystemController::flightSys;
std::vector<Flight> SystemController::currentFlightsResult;