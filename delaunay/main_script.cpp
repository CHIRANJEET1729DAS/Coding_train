#include <iostream>
#include <vector>
#include <random>
#include "delaunay.hpp"

int main() {
    int n;
    cout << "Enter number of points: ";
    cin >> n;

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(0.0, 100.0); 

    vector<vector<double>> coordinates;
    for (int i = 0; i < n; ++i) {
        double x = dist(gen);
        double y = dist(gen);
        coordinates.push_back({x, y});
    }

    cout << "Generated points:\n";
    for (const auto& point : coordinates) {
        cout << "(" << point[0] << ", " << point[1] << ")\n";
    }

    Delaunay delaunay(coordinates);
    delaunay.filter_delaunay_trios(coordinates);


    set<vector<double>> valid_trios = delaunay.get_valid_triangles();

    cout << "\nDelaunay Triangles (triplets of points):\n";
    // for (const auto& tri : valid_trios) {
    //     cout << "(" << tri[0] << ", " << tri[1] << "), "
    //               << "(" << tri[2] << ", " << tri[3] << "), "
    //               << "(" << tri[4] << ", " << tri[5] << ")\n";
    // }
    

    delaunay.export_to_csv("delaunay_output.csv");
    return 0;
}
