//
// Created by evgen on 07.03.2022.
//

#include <gmsh.h>
#include <set>
#include <cmath>
#include <iostream>

int main(int argc, char **argv) {
    gmsh::initialize();
    gmsh::model::add("cylindr");
    double lc = 10e-1;

    double radius = 10;
    double height = 3;
    for (int i = 0; i <= 1; i++) {
        int center = gmsh::model::geo::addPoint(0, 0, i*height, lc);
        int fst = gmsh::model::geo::addPoint(radius, 0, i*height, lc);
        int snd = gmsh::model::geo::addPoint(-radius / std::sqrt(2), radius / std::sqrt(2), i*height, lc);
        int trd = gmsh::model::geo::addPoint(-radius / std::sqrt(2), -radius / std::sqrt(2), i*height, lc);
        // curves
        int a = gmsh::model::geo::addCircleArc(fst, center, snd);
        std::cout << a << '\n';
        a = gmsh::model::geo::addCircleArc(snd, center, trd);
        std::cout << a << '\n';
        a = gmsh::model::geo::addCircleArc(trd, center, fst);
        std::cout << a << '\n';
    }
    // up and bottom
    int circle1 = gmsh::model::geo::addCurveLoop({1, 2, 3});
    circle1 = gmsh::model::geo::addSurfaceFilling({circle1});

    int circle2 = gmsh::model::geo::addCurveLoop({4, 5, 6});
    circle2 = gmsh::model::geo::addSurfaceFilling({circle2});

    // side surfaces
    int l1 = gmsh::model::geo::addLine(2, 6);
    int l2 = gmsh::model::geo::addLine(3, 7);
    int l3 = gmsh::model::geo::addLine(4, 8);

    int a = gmsh::model::geo::addCurveLoop({l1, 4, -l2, -1});
    int b = gmsh::model::geo::addCurveLoop({l2, 5, -l3, -2});
    int c = gmsh::model::geo::addCurveLoop({l3, 6, -l1, -3});

    a = gmsh::model::geo::addSurfaceFilling({a});
    b = gmsh::model::geo::addSurfaceFilling({b});
    c = gmsh::model::geo::addSurfaceFilling({c});

    int sl1 = gmsh::model::geo::addSurfaceLoop({circle1, circle2, a, b, c});

    int cyl = gmsh::model::geo::addVolume({sl1});
    // end of creation of cylindr

    gmsh::model::geo::synchronize();

    gmsh::model::mesh::generate(3);

    gmsh::write("cyl.msh");

    std::set<std::string> args(argv, argv + argc);
    if(!args.count("-nopopup")) gmsh::fltk::run();

    gmsh::finalize();

    return 0;
}
