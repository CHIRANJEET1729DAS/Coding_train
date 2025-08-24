#include "image_stippling.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>

Stippling::Stippling(const std::string& filepath) {
    cv::Mat image = cv::imread(filepath, cv::IMREAD_GRAYSCALE);
    if (image.empty()) {
        std::cerr << "Error loading image!" << std::endl;
        rows = 0;
        columns = 0;
        return; 
    }
    rows = image.rows;
    columns = image.cols;
    processed.resize(rows, std::vector<double>(columns, 0));

    for (double i = 0; i < rows; ++i) {
        for (double j = 0; j < columns; ++j) {
            double pixel_val = image.at<uchar>(i, j);
            if (pixel_val< 255){
                cout << pixel_val<< " for "<<i<<"  "<<j<<endl;
                processed[i][j] = 0;
            }else {
                processed[i][j] = 1;
            }
            // cout <<" processed "<<processed[i][j]<<endl;
        }
    }
}

void Stippling::processing(const std::vector<std::vector<double>>& input_processed) {
    processed = input_processed;
    rows = processed.size();
    columns = (rows > 0) ? processed[0].size() : 0;
    cout <<"processed properties"<<rows << columns <<endl;
    for (double i = rows - 1; i >= 0; --i) {
        for (double j = 0; j < columns; ++j) {
            if (processed[i][j] == 0) {
                coordinates.push_back({rows - i - 1, j});
            }
        }
    }
}


void Stippling::saveCoordinatesToCSV(std::vector<std::vector<double>>& coords, const std::string& filename){
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return;
    }
    file << "x,y\n";
    for (const auto& c : coords) {
        if (c.size() >= 2) {
            file << c[0] << "," << c[1] << "\n";
        }
    }
    file.close();
}

std::vector<std::vector<double>> Stippling::get_coordinates() const {
    return coordinates;
}

std::vector<std::vector<double>> Stippling::get_processed() const {
    return processed;
}
