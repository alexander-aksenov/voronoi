#include <iostream>
#include <vector>
#include <random_points.h>
#include <image_generator.h>
#include <bmp_writer.h>
#include <voronoi_diag.h>
#include <height_map.h>
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

    bool make_height_map;
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
        throw std::invalid_argument("Number of args less than 3: width, height, " \
                                    "points count[, seed, -d(iagram)/-h(eight map), output file, -c(olor)/-b(inary) output]");

    Args ret;
    char *end;

    ret.with_seed = false;
    ret.make_height_map = false;

    ret.width = parseUInt(argv[1]);
    ret.height = parseUInt(argv[2]);
    ret.points_cnt = parseUInt(argv[3]);

    if (argc >= 5) {
        ret.seed = parseUInt(argv[4]);
        if (ret.seed != 0)
            ret.with_seed = true;
    }

    if (argc >= 6) {
        if (std::string(argv[5]) == "-h")
            ret.make_height_map = true;
    }


    if (argc >= 7) {
        ret.to_file = true;
        ret.filepath = std::string(argv[6]);
        ret.show_color = true;
        ret.show_binary = true;
    }

    if (argc == 8) {
        if (std::string(argv[7]) == "-c")
            ret.show_binary = false;
        else if (std::string(argv[7]) == "-b")
            ret.show_color = false;
    }

    return ret;
}

int
main(int argc, char** argv)
{
    Args args;

    try {
        args = parseArgs(argc, argv);
    } catch (const std::exception &ex) {
        std::cerr << ex.what() << std::endl;
        return -1;
    }

    std::cout << "Field is " << args.width << "x" << args.height << " points " << args.points_cnt << std::endl;

    std::vector<Point> points;

    if (args.with_seed) {
        std::cout << "With seed " << args.seed << std::endl;
        points = RandomPoints::generate(args.width, args.height, args.points_cnt, args.seed);
    } else {
        points = RandomPoints::generate(args.width, args.height, args.points_cnt);
    }

    auto voronoi = VoronoiDiagram::makeVoronoiDiagram(args.width, args.height, points);
    if (args.make_height_map) {
        if (args.with_seed)
            HeightMap::makeHeightMap(voronoi, points, args.seed);
        else
            HeightMap::makeHeightMap(voronoi, points);
    }

    if (args.to_file) {
        std::string filename(argv[5]);
        ImageGenerator ig(args.width, args.height);
        if (args.show_color && !args.make_height_map)
            ig.addVoronoi(voronoi);
        else if (args.make_height_map)
            ig.addHeightMap(voronoi);
        if (args.show_binary) {
            auto bin_diagram = VoronoiDiagram::binarizeDiagram(voronoi);
            ig.addBinaryVoronoi(bin_diagram);
        }
        ig.addDots(points);
        BmpWriter bw(args.filepath, ig);
        bw.writeFile();
    } else {
        printPoints(points);
        printVoronoi(voronoi);
    }

    return 0;
}
