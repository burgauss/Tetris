#include "tetris.hpp"
#include <Windows.h>
using namespace std;

int main(int argc, char **argv)
{
    std:srand(std::time(0));
    auto tetris = std::make_shared<Tetris>();
    tetris->run();

    return 0;
}

//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{	 
//	std:srand(std::time(0));
//    auto tetris = std::make_shared<Tetris>();
//    tetris->run();
//
//    return 0;
//}
