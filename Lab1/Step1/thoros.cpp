//
// Created by evgen on 07.03.2022.
//

#include <gmsh.h>
#include <set>
#include <cmath>
#include <iostream>

int main(int argc, char **argv) {
    gmsh::initialize();
    gmsh::model::add("thoros");
    double lc = 30e-1;
    int center = gmsh::model::geo::addPoint(0, 0, 0, lc);

    for (int k = 0; k < 2; k++) {
        double s_r = 10 - 5 * k;
        double d_r = 5 * (k + 1);
        for (int i = 0; i <= 2; i++) {
            int fst = gmsh::model::geo::addPoint((s_r + i * d_r), 0, 0, lc);
            int snd = gmsh::model::geo::addPoint(-(s_r + i * d_r) / std::sqrt(2), (s_r + i * d_r) / std::sqrt(2), 0,
                                                 lc);
            int trd = gmsh::model::geo::addPoint(-(s_r + i * d_r) / std::sqrt(2), -(s_r + i * d_r) / std::sqrt(2), 0,
                                                 lc);
            if (i != 1) {
                gmsh::model::geo::addCircleArc(fst, center, snd);
                gmsh::model::geo::addCircleArc(snd, center, trd);
                gmsh::model::geo::addCircleArc(trd, center, fst);
            }
            std::cout << fst << snd << trd << '\n';
        }
        int mul1 = 9 * k;
        int mul2 = 12 * k;

        gmsh::model::geo::addCircleArc(2 + mul1, 5 + mul1, 8 + mul1, -1, 1, -1, 0);
        gmsh::model::geo::addCircleArc(8 + mul1, 5 + mul1, 2 + mul1, -1, 1, -1, 0);
        gmsh::model::geo::addCircleArc(3 + mul1, 6 + mul1, 9 + mul1, -1, 1, 1, 0);
        gmsh::model::geo::addCircleArc(9 + mul1, 6 + mul1, 3 + mul1, -1, 1, 1, 0);
        gmsh::model::geo::addCircleArc(4 + mul1, 7 + mul1, 10 + mul1, -1, -1, 1, 0);
        gmsh::model::geo::addCircleArc(10 + mul1, 7 + mul1, 4 + mul1, -1, -1, 1, 0);

        gmsh::model::geo::addCurveLoop({4 + mul2, -(9 + mul2), -(1 + mul2), 7 + mul2});
        gmsh::model::geo::addCurveLoop({4 + mul2, 10 + mul2, -(1 + mul2), -(8 + mul2)});
        gmsh::model::geo::addSurfaceFilling({1 + 6*k});
        gmsh::model::geo::addSurfaceFilling({2 + 6*k});

        gmsh::model::geo::addCurveLoop({5 + mul2, -(11 + mul2), -(2 + mul2), 9 + mul2});
        gmsh::model::geo::addCurveLoop({5 + mul2, 12 + mul2, -(2 + mul2), -(10 + mul2)});
        gmsh::model::geo::addSurfaceFilling({3 + 6*k});
        gmsh::model::geo::addSurfaceFilling({4 + 6*k});

        gmsh::model::geo::addCurveLoop({6 + mul2, -(7 + mul2), -(3 + mul2), 11 + mul2});
        gmsh::model::geo::addCurveLoop({6 + mul2, 8 + mul2, -(3 + mul2), -(12 + mul2)});
        gmsh::model::geo::addSurfaceFilling({5 + 6*k});
        gmsh::model::geo::addSurfaceFilling({6 + 6*k});

        gmsh::model::geo::addSurfaceLoop({1 + 6*k, 2 + 6*k, 3 + 6*k, 4 + 6*k, 5 + 6*k, 6 + 6*k});
    }

    gmsh::model::geo::addVolume({1,2});

    gmsh::model::geo::synchronize();

    gmsh::model::mesh::generate(3);

    gmsh::write("thoros.msh");

    std::set<std::string> args(argv, argv + argc);
    if (!args.count("-nopopup")) gmsh::fltk::run();

    gmsh::finalize();

    return 0;
}
