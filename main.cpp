#include <iostream>
#include <vector>
#include <random_points.h>
#include <bmp_writer.h>
#include <voronoi_diag.h>
#include <point.h>

struct Args {
    unsigned int width;
    unsigned int height;
    unsigned int points_cnt;

    bool with_seed;
    unsigned int seed;

    bool to_file;
    std::string filepath;
    bool show_color;
    bool show_binary;
};

static void
printPoints(std::vector<Point> &points)
{
    for (auto point : points)
        std::cout << point.x << ", " << point.y << std::endl;
}

static void
printVoronoi(std::vector<std::vector<Point>> &diag)
{
    for (unsigned int y = 0; y < diag[0].size(); y++) {
        for (unsigned int x = 0; x < diag.size(); x++) {
            std::cout << diag[x][y].x << "," << diag[x][y].y << " ";
        }
        std::cout << std::endl;
    }
}

static unsigned int
parseUInt(char* arg)
{
    char *end;
    return strtoul(arg, &end, 10);
}

static struct Args
parseArgs(int argc, char** argv)
{
    if (argc < 4)
        throw std::invalid_argument("Number of args less than 4");

    Args ret;
    char *end;

    ret.width = parseUInt(argv[1]);
    ret.height = parseUInt(argv[2]);
    ret.points_cnt = parseUInt(argv[3]);

    if (argc >= 5) {
        ret.seed = parseUInt(argv[4]);
        if (ret.seed != 0)
            ret.with_seed = true;
    }

    if (argc >= 6) {
        ret.to_file = true;
        ret.filepath = std::string(argv[5]);
        ret.show_color = true;
        ret.show_binary = true;
    }

    if (argc == 7) {
        if (std::string(argv[6]) == "-c")
            ret.show_binary = false;
        else if (std::string(argv[6]) == "-b")
            ret.show_color = false;
    }

    return ret;
}

int
main(int argc, char** argv)
{
    if (argc < 4) {
        std::cerr << "Number of args less than 4" << std::endl;
        return -1;
    }

    Args args = parseArgs(argc, argv);

    std::cout << "Field is " << args.width << "x" << args.height << " points " << args.points_cnt << std::endl;

    std::vector<Point> points;

    if (args.with_seed) {
        std::cout << "With seed " << args.seed << std::endl;
        points = RandomPoints::generate(args.width, args.height, args.points_cnt, args.seed);
    } else {
        points = RandomPoints::generate(args.width, args.height, args.points_cnt);
    }

    auto voronoi = VoronoiDiagram::makeVoronoiDiagram(args.width, args.height, points);
    auto bin_diagram = VoronoiDiagram::binarizeDiagram(voronoi);
    if (args.to_file) {
        std::string filename(argv[5]);
        BmpWriter bw(args.filepath, args.width, args.height);
        if (args.show_color)
            bw.showVoronoi(voronoi);
        if (args.show_binary)
            bw.showBinaryVoronoi(bin_diagram);
        bw.addDots(points);
        bw.writeFile();
    } else {
        printPoints(points);
        printVoronoi(voronoi);
    }

    return 0;
}
