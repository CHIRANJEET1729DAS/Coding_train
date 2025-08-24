#include "delaunay.hpp"

Delaunay::Delaunay(vector<vector<double>> &coordinates){
    int n = coordinates.size();
    for (int i =0 ;i<n;++i){
        for (int j =i+1 ;j<n;++j){
            for (int k=j+1 ;k<n;++k){
                vector<double> trio;
                trio.insert(trio.end(),coordinates[i].begin(),coordinates[i].end());
                trio.insert(trio.end(),coordinates[j].begin(),coordinates[j].end());
                trio.insert(trio.end(),coordinates[k].begin(),coordinates[k].end());
                triangles.insert(trio);
            }
        }
    }
};

Circle Delaunay::circumcircle(const vector<double>& tri){
    double x1 = tri[0], y1 = tri[1], x2 = tri[2], y2 = tri[3], x3 = tri[4], y3 = tri[5];

    double A = x2 - x1;
    double B = y2 - y1;
    double C = x3 - x1;
    double D = y3 - y1;

    double E = A * (x1 + x2) + B * (y1 + y2);
    double F = C * (x1 + x3) + D * (y1 + y3);

    double G = 2.0 * (A * (y3 - y2) - B * (x3 - x2));
    if (G == 0.0) return {0, 0, 0}; 

    double h = (D * E - B * F) / G;
    double k = (A * F - C * E) / G;
    double r = sqrt((x1 - h)*(x1 - h) + (y1 - k)*(y1 - k));
    return {h, k, r};
};

bool Delaunay::contains_other(const Circle& c, const vector<double>& tri ,const vector<vector<double>> &coordinates){
    for (const auto& p : coordinates) {
        if ((p[0]==tri[0] && p[1]==tri[1]) || 
            (p[0]==tri[2] && p[1]==tri[3]) || 
            (p[0]==tri[4] && p[1]==tri[5]))
            continue;
        double dx = p[0] - c.h, dy = p[1] - c.k;
        double dist = std::sqrt(dx*dx + dy*dy);
        if (dist < c.r - 1e-8) return true; 
    }
    return false;
};

void Delaunay::filter_delaunay_trios(vector<vector<double>> &coordinates){

    for (const std::vector<double>& tri : triangles) {
        Circle c = circumcircle(tri);
        if (c.r == 0.0) continue; 
        if (!contains_other(c, tri, coordinates)) {
            valid_triangles.insert(tri);
        }
    }
};

set<vector<double>> Delaunay::get_valid_triangles(){
    return valid_triangles; 
};

void Delaunay::export_to_csv(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file for writing: " << filename << "\n";
        return;
    }
    file << "x1,y1,x2,y2,x3,y3\n";

    for (const auto& tri : valid_triangles) {
        file << tri[0] << "," << tri[1] << "," 
             << tri[2] << "," << tri[3] << "," 
             << tri[4] << "," << tri[5] << "\n";
    }

    file.close();
}

