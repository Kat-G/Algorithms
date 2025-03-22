/** МИНИМАЛЬНЫЙ НАКРЫВАЮЩИЙ КРУГ
 * 
 * На плоскости даны n точек с координатами (x1, y1), (x2, y2), …, (xn, yn). Необходимо накрыть по крайней мере k из них 
 * кругом с центром на оси Ox. Найдите наименьший возможный радиус такого круга с точностью до 10-3.
 */

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

struct Point {
    int x_position;
    int y_position;
};

struct SegmentEnds {
    double position;
    int type;

    bool operator<(const SegmentEnds& other) const {
        if (position == other.position) {
            return type < other.type;
        }
        return position < other.position;
    }
};

bool IsPossibleCoverPoints(double radius, const std::vector<Point>& points,
                           int covered_size) {
    std::vector<SegmentEnds> segments;

    for (const auto& point : points) {
        if (point.y_position * point.y_position <= radius * radius) {
            double dx =
                sqrt(radius * radius - point.y_position * point.y_position);
            segments.push_back({point.x_position - dx, 1});
            segments.push_back({point.x_position + dx, -1});
        }
    }

    std::sort(segments.begin(), segments.end());

    int covered = 0;
    int maxCovered = 0;

    for (const auto& segment : segments) {
        covered += segment.type;
        maxCovered = std::max(maxCovered, covered);
    }

    return maxCovered >= covered_size;
}

double FindRadius(const std::vector<Point>& points, int covered_size) {
    double low_R = 0.0;
    double high_R = 1500.0;
    double eps = 1e-9;

    while (high_R - low_R > eps) {
        double middle_R = (low_R + high_R) / 2.0;
        if (IsPossibleCoverPoints(middle_R, points, covered_size)) {
            high_R = middle_R;
        } else {
            low_R = middle_R;
        }
    }

    return (low_R + high_R) / 2.0;
}

int main() {
    int size, covered_size;
    std::cin >> size >> covered_size;
    std::vector<Point> points(size);

    for (int i = 0; i < size; ++i) {
        std::cin >> points[i].x_position >> points[i].y_position;
    }

    double result = FindRadius(points, covered_size);

    std::cout.precision(6);
    std::cout << std::fixed << result << std::endl;

    return 0;
}
