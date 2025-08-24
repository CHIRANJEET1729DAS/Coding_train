#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "image_stippling.hpp"
#include "delaunay.hpp"

int main() {
    std::string filepath;
    std::cin >> filepath;
    std::string imagePath = filepath;

    Stippling stippling(imagePath);
    std::vector<std::vector<double>> processed = stippling.get_processed();
    stippling.processing(processed);
    std::vector<std::vector<double>> coords = stippling.get_coordinates();

    int num_points = 0;
    std::cout << "Enter number of points to pass to Delaunay (max " << coords.size() << "): ";
    std::cin >> num_points;
    if (num_points > (int)coords.size()) num_points = coords.size();

    std::srand(std::time(nullptr));

    std::vector<std::vector<double>> sampled_coords;
    std::vector<bool> chosen(coords.size(), false);

    while ((int)sampled_coords.size() < num_points) {
        int idx = std::rand() % coords.size();
        if (!chosen[idx]) {
            sampled_coords.push_back(coords[idx]);
            chosen[idx] = true;
        }
    }

    std::string filename = "sampled_coordinates.csv";
    stippling.saveCoordinatesToCSV(sampled_coords, filename);

    std::cout << "Coordinates of sampled stippling pixels:" << std::endl;
    for (const auto& coord : sampled_coords) {
        if (coord.size() >= 2)
            std::cout << "(" << coord[0] << "," << coord[1] << ")" << std::endl;
    }

    std::vector<std::vector<double>> swapped_coords;
    for (const auto& coord : sampled_coords) {
        if (coord.size() >= 2)
            swapped_coords.push_back({coord[1], coord[0]});
    }

    Delaunay delaunay(swapped_coords);
    delaunay.filter_delaunay_trios(swapped_coords);

    std::set<std::vector<double>> valid_trios = delaunay.get_valid_triangles();

    delaunay.export_to_csv("stippling_delaunay_output.csv");
    return 0;
}
