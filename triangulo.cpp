#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm>

using namespace std;

// Struct za 2D tocka
struct Point {
    double x, y;

    // sporedi dve tocki
    bool operator==(const Point& p) const {
        return x == p.x && y == p.y;
    }
};

// Struct za prava megu 2 tocki
struct Edge {
    Point p1, p2;

    //operator za sort tocki vo set
    bool operator<(const Edge& e) const {
        if (p1.x != e.p1.x) return p1.x < e.p1.x;
        if (p1.y != e.p1.y) return p1.y < e.p1.y; //shout out za mojot omilen operator
        if (p2.x != e.p2.x) return p2.x < e.p2.x;
        return p2.y < e.p2.y;
    }

    // operator za dali e isto(vektor nenasocen)
    bool operator==(const Edge& e) const {
        return (p1 == e.p1 && p2 == e.p2) || (p1 == e.p2 && p2 == e.p1);
    }
};

// Struct za triagolnik, neka trite negovi tocki
struct Triangle {
    Point p1, p2, p3;

    // dali tocka vo triangulo
    bool circumCircleContains(const Point& p) const {
        // translacija za p da e origin
        double ax = p1.x - p.x;
        double ay = p1.y - p.y;
        double bx = p2.x - p.x;
        double by = p2.y - p.y;
        double cx = p3.x - p.x;
        double cy = p3.y - p.y;

        // najdi determinant na matrix za dali tocka vo triangulo
        double det = (ax * ax + ay * ay) * (bx * cy - cx * by) -
                     (bx * bx + by * by) * (ax * cy - cx * ay) +
                     (cx * cx + cy * cy) * (ax * by - bx * ay);

        // ako determinant e pozitiven, tocka e vnatre
        return det > 0;
    }

    // dali triangl ima nekoja dadena tocka
    bool containsVertex(const Point& p) const {
        return p == p1 || p == p2 || p == p3;
    }

    // operator za dali triagolnici se ednakvi (vertex order be damned)
    bool operator==(const Triangle& t) const {
        vector<Point> pts1 = {p1, p2, p3};
        vector<Point> pts2 = {t.p1, t.p2, t.p3};

        // Sort tock za x pa y za comparacija
        sort(pts1.begin(), pts1.end(), [](const Point& a, const Point& b) {
            return a.x < b.x || (a.x == b.x && a.y < b.y);
        });
        sort(pts2.begin(), pts2.end(), [](const Point& a, const Point& b) {
            return a.x < b.x || (a.x == b.x && a.y < b.y);
        });

        return pts1 == pts2;
    }
};

// Func za Delaunay na set od tocki
vector<Triangle> delaunayTriangulation(const vector<Point>& points) {
    // 1: Neka bounding box na site tocki
    double minX = points[0].x;
    double minY = points[0].y;
    double maxX = minX;
    double maxY = minY;

    for (const auto& p : points) {
        if (p.x < minX) minX = p.x;
        if (p.y < minY) minY = p.y;
        if (p.x > maxX) maxX = p.x;
        if (p.y > maxY) maxY = p.y;
    }

    //max dimension od bounding box
    double dx = maxX - minX;
    double dy = maxY - minY;
    double deltaMax = max(dx, dy);

    // midpoint od bounding box
    double midX = (minX + maxX) / 2;
    double midY = (minY + maxY) / 2;

    // 2: napravi super-triangulo sho gi ima site tocki
    // Ova triangl e dovolno golemo za da gi ima site input tocki
    Point p1 = {midX - 20 * deltaMax, midY - deltaMax};
    Point p2 = {midX, midY + 20 * deltaMax};
    Point p3 = {midX + 20 * deltaMax, midY - deltaMax};

    // Inicoliziraj triangl lista so super-triangl
    vector<Triangle> triangles;
    triangles.push_back({p1, p2, p3});

    // 3: Insert tocki vo triangulation
    for (const auto& point : points) {
        vector<Triangle> badTriangles; // Triangl koj ja ima tockata
        vector<Edge> polygon;   // Poligon celi krakjni krajcinja
        // Najdi site triangl sho ne se valid zsh imat nova tocka
        for (const auto& triangle : triangles) {
            if (triangle.circumCircleContains(point)) {
                badTriangles.push_back(triangle);
            }
        }

        // 4: Neka kraj na poligon so removing bad triangulo
        vector<Edge> edges;
        for (const auto& triangle : badTriangles) {
            edges.push_back({triangle.p1, triangle.p2});
            edges.push_back({triangle.p2, triangle.p3});
            edges.push_back({triangle.p3, triangle.p1});
        }

        // Trni krajcinja sho se pojavuvaat dvapati
        multiset<Edge> edgeSet;
        for (const auto& edge : edges) {
            if (edgeSet.count(edge) == 0) {
                edgeSet.insert(edge);
            } else {
                // ako edge already E, remove it
                auto it = edgeSet.find(edge);
                if (it != edgeSet.end()) {
                    edgeSet.erase(it);
                }
            }
        }

        // Survivors (edges)
        polygon.assign(edgeSet.begin(), edgeSet.end());

        // 5: Remove bad triangl od triangulation
        triangles.erase(remove_if(triangles.begin(), triangles.end(),
            [&badTriangles](const Triangle& t) {
                return find(badTriangles.begin(), badTriangles.end(), t) != badTriangles.end();
            }), triangles.end());

        // 6: Re-triangulate poligoni so novi dodatoci
        for (const auto& edge : polygon) {
            triangles.push_back({edge.p1, edge.p2, point});
        }
    }

    // 7: Remove triangl so V od super-triangl
    // Ovie se nepotrebni
    triangles.erase(remove_if(triangles.begin(), triangles.end(),
        [p1, p2, p3](const Triangle& t) {
            return t.containsVertex(p1) || t.containsVertex(p2) || t.containsVertex(p3);
        }), triangles.end());

    // Return triangl za Delaunay triangulation
    return triangles;
}

int main() {
    // Ex set od tocki
    vector<Point> points = {
        {0, 0}, {1, 0}, {0, 1}, {1, 1},
        {0.5, 0.5}, {0.75, 0.75}, {0.25, 0.75}
    };

    // Neka Delaunay triangulation
    vector<Triangle> result = delaunayTriangulation(points);

    // Output res triangl
    cout << " res(triangls):\n";
    for (const auto& tri : result) {
        cout << "Triangulo: (" << tri.p1.x << ", " << tri.p1.y << ") - ("
             << tri.p2.x << ", " << tri.p2.y << ") - ("
             << tri.p3.x << ", " << tri.p3.y << ")\n";
    }

    return 0;
}