#ifndef DELAUNAY_HPP
#define DELAUNAY_HPP

#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

struct Circle{double h,k,r;};

class Delaunay{
    public:
        Delaunay(vector<vector<double>> &coordinates_);
        void Residue();
        void filter_delaunay_trios(vector<vector<double>> &coordinates_);
        Circle circumcircle(const vector<double>& tri);
        set<vector<double>> get_valid_triangles();
        bool contains_other(const Circle& c, const vector<double>& tri ,const vector<vector<double>> &coordinates);
        void export_to_csv(const std::string& filename);
    private:
        vector<vector<double>> coordinates;
        set<vector<double>> triangles,valid_triangles;
};


#endif