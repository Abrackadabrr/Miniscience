//
// Created by evgen on 07.03.2022.
//

#include <gmsh.h>
#include <set>
#include <cmath>

int main(int argc, char **argv) {
    gmsh::initialize();
    gmsh::model::add("cube");
    double lc = 10e-2;
    // add points
    for (int i = 0; i <= 1; i++)
        for (int j = 0; j <= 1; j++)
            for (int k = 0; k <= 1; k++)
                gmsh::model::geo::addPoint(i, j, k, lc);

    gmsh::model::geo::addLine(1, 2);
    gmsh::model::geo::addLine(2, 4);
    gmsh::model::geo::addLine(4, 3);
    gmsh::model::geo::addLine(3, 1);
    int back = gmsh::model::geo::addCurveLoop({1, 2, 3, 4});

    gmsh::model::geo::addLine(1+4, 2+4);
    gmsh::model::geo::addLine(2+4, 4+4);
    gmsh::model::geo::addLine(4+4, 3+4);
    gmsh::model::geo::addLine(3+4, 1+4);

    int fwd = gmsh::model::geo::addCurveLoop({5, 6, 7, 8});

    gmsh::model::geo::addLine(1, 5);
    gmsh::model::geo::addLine(2, 6);
    gmsh::model::geo::addLine(4, 8);
    gmsh::model::geo::addLine(3, 7);

    int left =  gmsh::model::geo::addCurveLoop({5, -10, -1, 9});
    int right =  gmsh::model::geo::addCurveLoop({12, -7, -11, 3});
    int bot =  gmsh::model::geo::addCurveLoop({4, 9, -8, -12});
    int up =  gmsh::model::geo::addCurveLoop({2, 11, -6, -10});

    for (int i = 0; i < 6; i++) gmsh::model::geo::addSurfaceFilling({i+1});

    int cube =  gmsh::model::geo::addSurfaceLoop({1, 2, 3, 4, 5, 6});

    gmsh::model::geo::addVolume({1});

    gmsh::model::geo::synchronize();

    gmsh::model::mesh::generate(3);

    std::set<std::string> args(argv, argv + argc);
    if(!args.count("-nopopup")) gmsh::fltk::run();
    gmsh::finalize();
    return 0;
}
