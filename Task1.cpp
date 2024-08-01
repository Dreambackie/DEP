#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>


class Location {
public:
    Location(const std::string& name, double latitude, double longitude)
        : name(name), latitude(latitude), longitude(longitude) {}

    std::string getName() const { return name; }
    double getLatitude() const { return latitude; }
    double getLongitude() const { return longitude; }

private:
    std::string name;
    double latitude;
    double longitude;
};

class LocationManager {
public:
    void addLocation(const Location& location) {
        locations.push_back(location);
    }

    void removeLocation(const std::string& name) {
        locations.erase(std::remove_if(locations.begin(), locations.end(),
            [&name](const Location& loc) { return loc.getName() == name; }), locations.end());
    }

    void listLocations() const {
        for (const auto& loc : locations) {
            std::cout << "Name: " << loc.getName() << ", Latitude: " << loc.getLatitude() << ", Longitude: " << loc.getLongitude() << std::endl;
        }
    }

private:
    std::vector<Location> locations;
};

class WeatherVariable {
public:
    void setVariable(const std::string& name, double value) {
        variables[name] = value;
    }

    double getVariable(const std::string& name) const {
        auto it = variables.find(name);
        if (it != variables.end()) {
            return it->second;
        }
        return 0.0; // Default value or handle it as needed
    }

    void listVariables() const {
        for (const auto& var : variables) {
            std::cout << "Variable: " << var.first << ", Value: " << var.second << std::endl;
        }
    }

private:
    std::unordered_map<std::string, double> variables;
};


