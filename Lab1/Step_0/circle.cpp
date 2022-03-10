//
// Created by evgen on 06.03.2022.
//

#include <gmsh.h>
#include <set>
#include <cmath>

int main(int argc, char **argv) {
    gmsh::initialize();
    gmsh::model::add("circle");
    double lc = 10e-2;
    // points
    double radius = 1;
    int center = gmsh::model::geo::addPoint(0, 0, 0, lc);
    int fst = gmsh::model::geo::addPoint(radius, 0, 0, lc);
    int snd = gmsh::model::geo::addPoint(-radius/std::sqrt(2), radius/std::sqrt(2), 0, lc);
    int trd =  gmsh::model::geo::addPoint(-radius/std::sqrt(2), -radius/std::sqrt(2), 0, lc);
    // curves
    gmsh::model::geo::addCircleArc(fst,center,snd, 1);
    gmsh::model::geo::addCircleArc(snd,center,trd, 2);
    gmsh::model::geo::addCircleArc(trd,center,fst, 3);
    // curves loops
    int circle1 = gmsh::model::geo::addCurveLoop({1, 2, 3});
    gmsh::model::geo::addPlaneSurface({1}, circle1);
    gmsh::model::geo::synchronize();
    gmsh::model::mesh::generate(2);
    gmsh::write("circle.msh");

    std::set<std::string> args(argv, argv + argc);
    if(!args.count("-nopopup")) gmsh::fltk::run();
    gmsh::finalize();

    return 0;
}