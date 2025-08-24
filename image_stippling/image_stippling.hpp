#ifndef STIPPLING_HPP
#define STIPPLING_HPP

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class Stippling {
public:
    Stippling(const std::string& filepath);
    void processing(const std::vector<std::vector<double>>& processed);
    std::vector<std::vector<double>> get_coordinates() const;
    vector<vector<double>> get_processed() const;
    void saveCoordinatesToCSV(std::vector<std::vector<double>>& coords, const std::string& filename);
private:
    double rows = 0;
    double columns = 0;
    std::vector<std::vector<double>> processed;
    std::vector<std::vector<double>> coordinates;
};

#endif
