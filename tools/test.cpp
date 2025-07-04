#include "../tetris.hpp"
#include <filesystem>
#include <fstream>
#include <vector>

/*void emptyConstructorTest() {
    piece p;
    std::cout << "Empty constructor " << p.side();
    if (p.empty() && !p.full() && p.side() == 0 && p.color() == 0) {
        std::cout << "\033[32m"; // Set text color to green
        std::cout << " --> OK 🎉" << std::endl;
    } else {
        std::cout << "\033[31m"; // Set text color to red
        std::cout << "--> NOP 😭 Error in empty constructor or p.full() p.side() p.color()" << std::endl;
    }
    std::cout << "\033[0m"; // Reset text color
}

void testPieceConstructor(uint32_t s, uint32_t c, bool expectFailure) {
    std::cout << "\033[0m"; // Reset text color
    std::cout << "Testing piece constructor with size " << s << " and color " << (int)c;
    try {
        piece p(s, c);
        if (expectFailure) {
            std::cout << "\033[31m"; // Set text color to red
            std::cout << " --> NOP 😭 Expected failure but got success" << std::endl;
        } else {
            if (p.empty() && !p.full() && p.side() == s && p.color() == (uint8_t)c) {
                std::cout << "\033[32m"; // Set text color to green
                std::cout << " --> OK 🎉" << std::endl;
            } else {
                std::cout << "\033[31m"; // Set text color to red
                std::cout << " --> NOP 😭 Error in piece constructor or p.full() p.side() p.color()" << std::endl;
            }
        }
    } catch (tetris_exception const &e) {
        if (expectFailure) {
            std::cout << "\033[32m"; // Set text color to green
            std::cout << " --> OK 🎉 Caught exception: " << e.what() << std::endl;
        } else {
            std::cout << "\033[31m"; // Set text color to red
            std::cout << " --> NOP 😭 Expected success but got failure: " << e.what() << std::endl;
        }
    }
    std::cout << "\033[0m"; // Reset text color
}

void cutrowTest (int i, bool expectFailure) {
    std::cout << "Testing cutrow with index " << i << std::endl;
    piece p(4, 1);
    p(0, 0) = true;
    p(0, 1) = true;
    p(1, 0) = true;
    p(1, 1) = true;
    p(2, 2) = true;
    p(3, 3) = true;
    p.print_ascii_art(std::cout);
    try {
        p.cut_row(i);
        if (expectFailure) {
            std::cout << "\033[31m"; // Set text color to red
            std::cout << " --> NOP 😭 Expected failure but got success" << std::endl;
        } else {
            p.print_ascii_art(std::cout);
            std::cout << "\033[32m"; // Set text color to green
            std::cout << " --> OK 🎉" << std::endl;
        }
    } catch (tetris_exception const &e) {
        if (expectFailure) {
            std::cout << "\033[32m"; // Set text color to green
            std::cout << " --> OK 🎉 Caught exception: " << e.what() << std::endl;
        } else {
            std::cout << "\033[31m"; // Set text color to red
            std::cout << " --> NOP 😭 Expected success but got failure: " << e.what() << std::endl;
        }
    }
    std::cout << "\033[0m"; // Reset text color
}

void rotateTest() {
    piece p(2, 1);
    p(0, 1) = true;
    p(1, 1) = true;
    p(1, 1) = true;
    p(1, 0) = true;

    std::cout << "Before rotation:" << std::endl;
    p.print_ascii_art(std::cout);
    p.rotate();
    p.print_ascii_art(std::cout);
    p.rotate();
    p.print_ascii_art(std::cout);
    p.rotate();
    p.print_ascii_art(std::cout);
    p.rotate();
    p.print_ascii_art(std::cout);
}*/

void parserTest() {
    std::cout << "*** Testing tetris parser with dataset ***" << std::endl;
    std::string path = "tools/testDataset/";
    std::vector<std::string> files;
    for (const auto &entry : std::filesystem::directory_iterator(path))
    {
        files.push_back(entry.path().string());
    }

    for (const auto &file : files)
    {
        // Extract the filename from the path
        std::string filename = file.substr(file.find_last_of('/') + 1);
        std::cout << "File: " << filename;
        std::ifstream in(file);
        if (!in.good())
        {
            std::cerr << "cannot open file '" << file << "'" << std::endl;
            return;
        }
        bool expectFailure = file.find("Malformed") != std::string::npos;
        try
        {
            piece p;
            in >> p;
            if (expectFailure)
            {
                std::cout << "\033[31m"; // Set text color to red
                std::cerr << " --> NOP 😭 Expected failure but got success for file: " << file << std::endl;
                std::cout << "\033[0m"; // Reset text color
            }
            else
            {
                std::cout << "\033[32m"; // Set text color to green
                std::cout << " --> OK 🎉" << std::endl;
                std::cout << "\033[0m"; // Reset text color
                p.print_ascii_art(std::cout);
                std::cout << "Piece p: " << p << std::endl;
            }
        }
        catch (tetris_exception const &e)
        {
            if (expectFailure)
            {
                std::cout << "\033[32m"; // Set text color to green
                std::cout << " --> OK 🎉 ";
                std::cerr << " Caught exception for file '" << file << "': " << e.what() << std::endl;
                std::cout << "\033[0m"; // Reset text color
            }
            else
            {
                std::cout << "\033[31m"; // Set text color to red
                std::cerr << " --> NOP 😭 Expected success but got failure for file: " << file;
                std::cerr << " Caught exception for file '" << file << "': " << e.what() << std::endl;
                std::cout << "\033[0m"; // Reset text color
            }
        }
    }
    return;
}

int main () {
    /*std::cout << "*** Testing tetris functions ***" << std::endl;
    
    emptyConstructorTest();

    testPieceConstructor(2, 1, false);
    testPieceConstructor(4, 2, false);
    testPieceConstructor(8, 3, false);
    testPieceConstructor(5, 4, true); // Invalid size
    testPieceConstructor(2, -1, true); // Invalid color
    testPieceConstructor(2, 0, true); // Invalid color
    testPieceConstructor(0, 1, true); // Invalid size*/

    /*cutrowTest(0, false);
    cutrowTest(1, false);
    cutrowTest(2, false);
    cutrowTest(3, false);
    cutrowTest(5, true); // Invalid cut row*/

    //rotateTest();

    //parserTest();

    /*std::cout << "*** Testing tetris class ***" << std::endl;

    try{
    tetris t(4, 7, 0);

    piece p1 (2, 1);
    p1(0, 0) = true;
    p1(0, 1) = true;
    p1(1, 0) = true;
    p1(1, 1) = true;
    piece p2 (2, 2);
    p2(0, 0) = true;
    p2(0, 1) = true;
    p2(1, 0) = true;
    p2(1, 1) = true;
    piece p3 (2, 3);
    p3(0, 0) = true;
    p3(0, 1) = true;
    p3(1, 0) = true;
    p3(1, 1) = true;


    t.add(p1, 0, 0);
    t.add(p2, 2, 0);
    t.add(p3, 1, 2);
    t.add(p3, 1, 4);

    //t.print_ascii_art(std::cout);

    tetris t2 = t; // Copy constructor
    std::cout << "Original tetris:\n";
    t.print_ascii_art(std::cout);
    std::cout << "Copied tetris:\n";
    t2.print_ascii_art(std::cout);

    if (t == t2)
        std::cout << "\033[32mCopy constructor OK 🎉\033[0m" << std::endl;
    else
        std::cout << "\033[31mCopy constructor NOP 😭\033[0m" << std::endl;
    
    
    } catch (tetris_exception const &e) {
        std::cout << e.what() << std::endl;
    }



    std::cout << "*** End of tests ***" << std::endl;*/
    return 0;
}
