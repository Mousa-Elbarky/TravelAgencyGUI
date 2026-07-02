#pragma once
#include <string>
#include <vector>

class Flight {
public:
    int id;
    std::string city;
    double price;
    std::vector<std::string> times;

    Flight(int i, std::string c, double p, std::vector<std::string> t) {
        id = i; city = c; price = p; times = t;
    }
    Flight() { id = 0; city = ""; price = 0; }
};

class FlightSystem {
public:
    std::vector<Flight> flightsList;
    void loadFlightsData() {
        flightsList.push_back(Flight(1, "Saudi Arabia", 1200, { "02:00 pm", "08:30 pm" }));
        flightsList.push_back(Flight(2, "Saudi Arabia", 1400, { "11:00 am", "09:00 pm" }));
        flightsList.push_back(Flight(3, "UAE", 1500, { "09:00 am", "05:15 pm" }));
        flightsList.push_back(Flight(4, "UAE", 1700, { "01:00 pm", "10:00 pm" }));
        flightsList.push_back(Flight(5, "Turkey", 1800, { "12:00 pm", "07:30 pm" }));
        flightsList.push_back(Flight(6, "Turkey", 2000, { "08:00 am", "06:00 pm" }));
    }

    std::vector<Flight> searchFlightsByCity(std::string city) {
        std::vector<Flight> result;
        for (size_t i = 0; i < flightsList.size(); i++) {
            if (flightsList[i].city == city) {
                result.push_back(flightsList[i]);
            }
        }
        return result;
    }
};

class SystemController {
public:
    static double totalCost;
    static std::string selectedCountry;
    static std::string selectedActivity;
    static std::string activityTime;

    static FlightSystem flightSys;
    static std::vector<Flight> currentFlightsResult;

    static void addToTotal(double price) {
        totalCost += price;
    }

    static void resetTotal() {
        totalCost = 0.0;
    }
};